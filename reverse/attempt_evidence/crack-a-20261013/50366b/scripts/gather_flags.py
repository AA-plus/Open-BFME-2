from trial import *
base=(ROOT/'build/crack-a/gather-scope-4/c1.cpp').read_text()
variants=[]
for flag in ['/Zc:forScope','/Zc:forScope-','/Og','/Ow','/Oa','/Ob1','/EHsc','/G6','/G5','/Os']:
    variants.append((str(len(variants)),base.replace('/Ireference/shims/bfmealloc','/Ireference/shims/bfmealloc '+flag,1)))
old='template <> RegionInfoMap::iterator RegionInfoMap::insert(RegionInfoMap::iterator, const RegionInfoMap::value_type &);'
variants.append(('visible',base.replace(old,'template <> __declspec(noinline) RegionInfoMap::iterator RegionInfoMap::insert(RegionInfoMap::iterator position, const RegionInfoMap::value_type &value) {return _M_t.insert_equal(position,value);}')))
for tag,s in variants:
    r=run(s,'gather-flags-'+tag,'gather')
    if r.get('exact'):break
