from trial import *
for sc in ['gather-base','gather-scope-4']:
 base=(ROOT/'build/crack-a'/sc/'c1.cpp').read_text()
 original='void LWAIWorldInformation::GatherWorldInformation()'
 for mode in range(8):
  b=base.replace('void GatherWorldInformation();','void GatherWorldInformation();\n __forceinline void GatherImpl();')
  b=b.replace(original,'__forceinline void LWAIWorldInformation::GatherImpl()')
  b+='\n'+original+'{GatherImpl();}\n'
  if mode&1:
   spec='namespace _STL {'+''.join('template<> __forceinline pair<int,'+ty+'>::pair(const int &a,const '+ty+'&b):first(a),second(b){}' for ty in ['Rva00501656','Rva00501776','Rva00501E3FElement'])+'}\n'
   b=b.replace('class LWAIWorldInformation',spec+'class LWAIWorldInformation')
  if mode//2==1:
   b=b.replace('void GatherImpl();','void GatherImpl() const;').replace('void LWAIWorldInformation::GatherImpl()','void LWAIWorldInformation::GatherImpl() const')
   b=b.replace('PlayerInfoMap m_PlayerInfo;','mutable PlayerInfoMap m_PlayerInfo;').replace('RegionInfoMap m_RegionInfo;','mutable RegionInfoMap m_RegionInfo;').replace('IntIntMap m_RegionInfoByRegion;','mutable IntIntMap m_RegionInfoByRegion;')
  elif mode//2==2:
   b=b.replace('__forceinline void GatherImpl();','template<int Tag> __forceinline void GatherImpl();').replace('__forceinline void LWAIWorldInformation::GatherImpl()','template<int Tag> __forceinline void LWAIWorldInformation::GatherImpl()').replace('{GatherImpl();}','{GatherImpl<0>();}')
  elif mode//2==3:
   b=b.replace('__forceinline void GatherImpl();','static __forceinline void GatherImpl(LWAIWorldInformation *self);')
   b=b.replace('__forceinline void LWAIWorldInformation::GatherImpl()','__forceinline void LWAIWorldInformation::GatherImpl(LWAIWorldInformation *self)')
   at=b.index('__forceinline void LWAIWorldInformation::GatherImpl(');tail=b[at:]
   for member in ['m_PlayerInfo','m_RegionInfo','m_RegionInfoByRegion']:tail=re.sub(r'\b'+member+r'\b','self->'+member,tail)
   b=b[:at]+tail.replace('{GatherImpl();}','{GatherImpl(this);}')
  r=run(b,'gather-wholeinline-'+sc+'-'+str(mode),'gather')
  if r.get('exact'):raise SystemExit()
