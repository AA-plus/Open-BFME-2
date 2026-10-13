from trial import *
import permute
base=(ROOT/'build/crack-a/gather-base/c1.cpp').read_text()
dest=ROOT/'build/crack-a/gather-original-stacksearch'
dest.mkdir(exist_ok=True)
s=permute.Scorer('0x0050366b','?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ',1706,dest)
score,exact=s.score(base)
out,best,exact=permute.stack_search(base,s,score,permute.focus_of(s.symbol),500)
(dest/'best.cpp').write_text(out)
(dest/'summary.json').write_text(json.dumps(dict(start=score,best=best,exact=exact,trials=s.trials)))
print(dict(start=score,best=best,exact=exact,trials=s.trials),flush=True)
