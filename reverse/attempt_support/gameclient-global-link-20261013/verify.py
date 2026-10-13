"""Read-only relocation and definition proof for the GameClient binding repair."""
import csv
import json
import pickle
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import build
import link_census

CONSUMERS = {
    "Code/GameEngine/Source/GameClient/System/ParticleBaseConstructor.cpp": "0x001F4B63",
    "Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp": "0x0038CBBA",
}
NAME = "?TheGameClient@@3PAVGameClient@@A"
OLD = "?TheGameClient@@3PAVClientFrameSubsystem@@A"
proof = []
with (ROOT / "reverse/functions.csv").open(newline="") as handle:
    for row in csv.DictReader(handle):
        if CONSUMERS.get(row["source"]) != row["target_rva"]:
            continue
        obj = build.row_object(row)
        size = int(row["target_size"], 0)
        body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        target = build.read_target_bytes(int(row["target_rva"], 0), size)
        bindings = [(offset, kind, name) for offset, kind, name in relocs if "TheGameClient@@" in name]
        assert len(bindings) == 1, bindings
        offset, kind, name = bindings[0]
        assert (kind, name) == (6, NAME), bindings
        assert int.from_bytes(body[offset:offset + 4], "little") == 0
        assert int.from_bytes(target[offset:offset + 4], "little") == 0x00DFE77C
        assert OLD not in {symbol["name"] for symbol in link_census._coff_symbols(obj.read_bytes())}
        source = (ROOT / row["source"]).resolve()
        assert link_census.object_current(source, obj, allow_fresh=False), row["source"]
        proof.append({"source": row["source"], "rva": row["target_rva"], "offset": offset,
                      "kind": kind, "name": name, "addend": 0, "target_va": "0x00DFE77C"})
assert len(proof) == 2, proof
provider = ROOT / "Code/GameEngine/Source/GameClient/GameClient.cpp"
definitions = [symbol for symbol in link_census._coff_symbols(build.obj_path(provider).read_bytes())
               if symbol["name"] == NAME and symbol["section"] > 0 and symbol["storage"] == 2]
assert len(definitions) == 1, definitions
with (ROOT / "build/link_census/link_index.pkl").open("rb") as handle:
    meta = pickle.load(handle)["meta"]
print(json.dumps({"census": meta, "consumer_self_strict": True, "relocations": proof,
                  "provider_definition": definitions[0],
                  "provider_self_strict": link_census.object_current(provider, build.obj_path(provider),
                                                                     allow_fresh=False)}, indent=2))
