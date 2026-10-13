from trial import *
import permute
out=ROOT/'build/crack-a/permute-combinations'
out.mkdir(exist_ok=True)
permute.OUT=out
# Its default advisory triage stops on any displacement-only gap. We have
# independently established these are local allocation choices, not layout facts.
permute.unreachable=lambda *args:None
old_score=permute.Scorer.score
def score(self,source):
    before=self.trials
    result=old_score(self,source)
    if self.trials!=before:
        (out/('trial-'+str(self.trials)+'.cpp')).write_text(source)
        with (out/'scores.jsonl').open('a') as f:f.write(json.dumps(dict(trial=self.trials,score=result[0],exact=result[1]))+'\n')
        if self.trials%20==0 or result[1]: print(dict(trial=self.trials,score=result[0],exact=result[1]),flush=True)
    return result
permute.Scorer.score=score
print(permute.permute('0x0050366b',minutes=10,seed=20261013),flush=True)
