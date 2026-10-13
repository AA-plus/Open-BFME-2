from trial import *
import subprocess
root=build.vc71_root();dest=ROOT/'build/crack-a/gather-ltcg';dest.mkdir(exist_ok=True)
obj=ROOT/'build/crack-a/gather-backend-17/c1.obj'
cmd=[str(root/'Vc7/bin/link.exe'),'/nologo','/DLL','/NOENTRY','/NODEFAULTLIB','/FORCE:UNRESOLVED','/LTCG','/OPT:NOREF','/EXPORT:?GatherWorldInformation@LWAIWorldInformation@@QAEXXZ','/OUT:'+str(dest/'probe.dll'),'/MAP:'+str(dest/'probe.map'),str(obj)]
r=subprocess.run(cmd,cwd=dest,env=build.compiler_environment(root),capture_output=True,text=True)
(dest/'link.txt').write_text(r.stdout+r.stderr)
print('exit',r.returncode);print((r.stdout+r.stderr)[-1800:])
