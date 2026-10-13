// ?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z
// partial score=0.7925762250054933 date=2026-10-13
// cl: /I. /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
#include "reverse/attempt_evidence/pathfinder_hierarchy/owner_context.inc"

// Native2F71A6..2F83A3 RET32,4605B; WB D4FAE0, pathfinder.cpp7421..7827.
// Complete target reconstruction from the clean ZH/BF1 hierarchical search.
// BF1 donor cee35b7d8ca077d7255f1c39cb69e9fd9627aa85, AIPathfind.cpp5852.
Path *Pathfinder::internal_findHierarchicalPath(Bool isHuman,
 LocomotorSurfaceTypeMask surfaces,Object *obj,const Coord3D *from,
 const Coord3D *rawTo,Bool crusher,Bool closestOK,Coord3D *adjustedTo)
{
 if(rawTo->x==0.0f && rawTo->y==0.0f)return 0;
 if(!m_isMapReady)return 0;
 HierarchyPoint adjustTo(*rawTo);
 Coord3D *to=&adjustTo;
 HierarchyPoint clipFrom(*from);
 rva002E75A3(&clipFrom,&adjustTo);
 m_isTunneling=false;
 Bool useMineshaft=false;
 HierarchyPoint originalTo(adjustTo);
 if(TheMineshaftPortalNetworkManager->hasUsableNetwork(obj->getControllingPlayer())) {
  float startDistance=0.0f,endDistance=0.0f;
  for(Waypoint *wp=((HierarchyTerrain *)TheTerrainLogic)->getFirstWaypoint();wp;wp=wp->next) {
   if(wp->type==8 && (unsigned char)((Rva002E6ECA *)wp)->get() && wp->isValidUnitType(obj)) {
    if(rva001E3647Pos(TheTerrainLogic->getLayerForDestination(0,&wp->location),&wp->location)) {
     HierarchyPoint delta(wp->location);
     delta.x-=obj->position[0];delta.y-=obj->position[1];delta.z-=obj->position[2];
     float dist=delta.x*delta.x+delta.y*delta.y;
     if(!m_srcMineshaft || dist<startDistance) {m_srcMineshaft=(PathfinderMineshaft *)wp;startDistance=dist;}
     delta=wp->location;
     delta.x-=rawTo->x;delta.y-=rawTo->y;delta.z-=rawTo->z;
     dist=delta.x*delta.x+delta.y*delta.y;
     if(!m_destMineshaft || dist<endDistance) {m_destMineshaft=(PathfinderMineshaft *)wp;endDistance=dist;}
    }
   }
  }
  if(m_srcMineshaft && m_destMineshaft && m_srcMineshaft!=m_destMineshaft &&
     QuickDoesPathExist(obj,from,&m_srcMineshaft->m_position,0) &&
     QuickDoesPathExist(obj,&m_destMineshaft->m_position,rawTo,0)) {
   useMineshaft=true;adjustTo=m_srcMineshaft->m_position;rva002E75A3(&clipFrom,&adjustTo);
  } else {m_srcMineshaft=0;m_destMineshaft=0;}
 }
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(0,to);
 ICoord2D cell;Rva002E7875WorldToCell(&cell,true,to);
 PathfindCell *goalCell=getCell(destinationLayer,cell.x,cell.y);
 if(!goalCell)return 0;
 goalCell->allocateInfo((In002E6BA1 *)&cell);
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,from);
 PathfindCell *parentCell=rva002E8BF8(layer,&clipFrom);
 if(!parentCell)return 0;
 if(parentCell==goalCell) {goalCell->ReleaseInfo();return 0;}
 ICoord2D startCellNdx;
 parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&startCellNdx,true,&clipFrom));
 if((unsigned char)parentCell->m_info%16==4 &&
    (parentCell->m_pathInfo?parentCell->m_pathInfo->obstacleID:(ObjectID)0)!=m_ignoreObstacleID) {
  goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;
 }
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 Bool layerFlag=obj->rva0028AC62();
 Bool objectFlag=obj->rva0028AFBB();
 HierarchySearchOptions options={surfaces,!flag,objectFlag,priority-1,layerFlag};
 Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)&m_zoneManager;
 Int zone1=zones->rva0053241F(&options,parentCell->quickZone());
 Int zone2=zones->rva0053241F(&options,goalCell->quickZone());
 if((unsigned char)goalCell->m_info%16==4)zone2=zones->rva0053241F(&options,zones->rva00531FD4(&options,(unsigned short)zone2));
 if(!closestOK && !rva002F4115(obj,zone1,zone2,0)) {goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;}
 parentCell->StartPathfind((Int)goalCell);
 parentCell->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parentCell,goalCell);
 Int cellCount=0;
 unsigned short goalBlockZone;
 ICoord2D goalBlockNdx;
 if((unsigned char)Rva002E6E6CGet(goalCell->getLayer())) {
  goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
 } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
 AddToOpenList(parentCell);
 if(!(unsigned char)Rva002E6E6CGet(parentCell->getLayer())) {
  HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[parentCell->getLayer()];
  ICoord2D ndx=bridge->start,toNdx=bridge->end;
  PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
  PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
  if(end && start) {
   rva002F36E5();parentCell->PutOnClosedList(&m_closedList);
   start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);++cellCount;
   Int curCost=start->CalcCostToHierGoal(parentCell),remCost=start->CalcCostToHierGoal(goalCell);
   start->m_pathInfo->costSoFar=(unsigned short)curCost;start->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(start,parentCell);AddToOpenList(start);
   ++cellCount;end->allocateInfo((In002E6BA1 *)&toNdx);
   curCost=end->CalcCostToHierGoal(parentCell);remCost=end->CalcCostToHierGoal(goalCell);
   end->m_pathInfo->costSoFar=(unsigned short)curCost;end->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(end,parentCell);AddToOpenList(end);
  }
 }
 PathfindCell *closestCell=0,*initialCell=parentCell;
 float closestDistSqr=1.0e12f;
 while((parentCell=rva002F36E5())!=0) {
  parentCell->PutOnClosedList(&m_closedList);
  unsigned short parentZone;
  if((unsigned char)Rva002E6E6CGet(parentCell->getLayer()))
   parentZone=zones->rva00532041((Int)&options,parentCell->getXIndex(),parentCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  else parentZone=parentCell->quickZone();
  Bool reachedGoal=false;
  Int blockX=parentCell->getXIndex()/16,blockY=parentCell->getYIndex()/16;
  if(parentZone==goalBlockZone && (goalBlockNdx.x==-1 || (blockX==goalBlockNdx.x && blockY==goalBlockNdx.y)))reachedGoal=true;
  Disp32IntPair extent;((Rva005315B0IntPairField *)&m_zoneManager)->get(extent);
  if(!reachedGoal && m_zoneManager.rva00532069(parentCell->getXIndex(),parentCell->getYIndex())) {
   for(Int i=0;i<=15;++i) {
    HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
    if(!((Rva0036666B *)bridge)->rva0036666B() || bridge->destroyed)continue;
    ICoord2D ndx=bridge->start,toNdx=bridge->end;
    if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
    if(ndx.x<0 || ndx.y<0)continue;
    if(toNdx.x<0 || toNdx.y<0)continue;
    if(ndx.x/16==blockX && ndx.y/16==blockY) {
     Int bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
     if(bridgeZone!=parentZone) {
      if(ndx.x/16==toNdx.x/16 && ndx.y/16==toNdx.y/16) {
       ICoord2D temp=ndx;ndx=toNdx;toNdx=temp;
       bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      }
      if(bridgeZone!=parentZone)continue;
     }
     if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
     PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
     if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
     PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
     if(!start || start==end)continue;
     if(start!=parentCell) {
      start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
      if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
     }
     end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start);++cellCount;
     Int curCost=end->CalcCostToHierGoal(start),remCost=end->CalcCostToHierGoal(goalCell);
     end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
     end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
     hierarchySetParent(end,start);AddToOpenList(end);
    }
   }
  }
  Bool wasMineshaft=useMineshaft;
  if(reachedGoal) {
   if(useMineshaft) {
    useMineshaft=false;reachedGoal=false;adjustTo=originalTo;
    PathfindLayerEnum dest=TheTerrainLogic->getLayerForDestination(0,to);
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,to);
    goalCell=getCell(dest,ndx.x,ndx.y);goalCell->allocateInfo((In002E6BA1 *)&ndx);
    zone2=zones->rva0053241F(&options,goalCell->quickZone());
    if((unsigned char)Rva002E6E6CGet(goalCell->getLayer())) {
     goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
     goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
    } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
   }
   if(reachedGoal)goto goalFound;
  }
  if(m_zoneManager.rva005315C8(parentCell->getXIndex(),parentCell->getYIndex())) {
   Int i=0;
   for(Waypoint *wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),i);
       wp;wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),++i)) {
    if(wp->type==8 && !wasMineshaft)continue;
    if(!wp->isValidUnitType(obj))continue;
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,&wp->location);
    for(Int j=0;j<wp->linkCount;++j) {
     Waypoint *link=wp->getLink(j);if(!link)continue;
     ICoord2D toNdx;Rva002E7875WorldToCell(&toNdx,true,&link->location);
     HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
     if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
     if(ndx.x<0 || ndx.y<0)continue;
     if(toNdx.x<0 || toNdx.y<0)continue;
     if(ndx.x/16==blockX && ndx.y/16==blockY) {
      unsigned short bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      if(bridgeZone!=parentZone)continue;
      if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
      PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
      if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
      PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
      if(!start)continue;
      if(start!=parentCell) {
       start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
       if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
      }
      end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start,wp);++cellCount;
      Int curCost=0;if(wp->type==8)curCost=500;else curCost=end->CalcCostToHierGoal(start);
      Int remCost=end->CalcCostToHierGoal(goalCell);
      end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
      end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
      hierarchySetParent(end,start,wp);AddToOpenList(end);
     }
    }
   }
  }
  if(reachedGoal)goto goalFound;
  float dx=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getXIndex()-parentCell->getXIndex());
  float dy=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getYIndex()-parentCell->getYIndex());
  float distance=dx*dx+dy*dy;
  if(distance<closestDistSqr) {closestCell=parentCell;closestDistSqr=distance;}
  unsigned short examinedZones[16];Int examinedCount=0;
  if(blockX>0) {
   examinedCount=0;
   for(Int k=1;k<=16;++k) {
    Int offset=k/2;if(k&1)offset=-offset;
    ICoord2D ndx={ blockX*16,blockY*16+8+offset },delta={ -1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (m_extentLowX<=ndx.x && ndx.x<=m_extentHighX && m_extentLowY<=ndx.y && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockX<extent.x-1) {
   examinedCount=0;
   for(Int k=1;k<=16;++k) {
    Int offset=k/2;if(k&1)offset=-offset;
    ICoord2D ndx={ blockX*16+15,blockY*16+8+offset },delta={ 1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (m_extentLowX<=ndx.x && ndx.x<=m_extentHighX && m_extentLowY<=ndx.y && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY>0) {
   examinedCount=0;
   for(Int k=1;k<=16;++k) {
    Int offset=k/2;if(k&1)offset=-offset;
    ICoord2D ndx={ blockX*16+8+offset,blockY*16 },delta={ 0,-1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (m_extentLowX<=ndx.x && ndx.x<=m_extentHighX && m_extentLowY<=ndx.y && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY<extent.y-1) {
   examinedCount=0;
   for(Int k=1;k<=16;++k) {
    Int offset=k/2;if(k&1)offset=-offset;
    ICoord2D ndx={ blockX*16+8+offset,blockY*16+15 },delta={ 0,1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (m_extentLowX<=ndx.x && ndx.x<=m_extentHighX && m_extentLowY<=ndx.y && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
 }
 if(closestOK && closestCell && closestCell!=initialCell) {
  m_isTunneling=false;
  Coord3D closest;
  *adjustedTo=*(Coord3D *)Rva002E8C4DCall((Int)&closest,1,(Rva002E8C23Pair *)closestCell->m_pathInfo,1);
  Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)closestCell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
  rva002F40E7();goalCell->ReleaseInfo();return path;
 }
 _STL::vector<Gen_p12pod> *hops=(_STL::vector<Gen_p12pod> *)&m_1C1CC;hops->erase(hops->begin(),hops->end());
 m_isTunneling=false;rva002F40E7();goalCell->ReleaseInfo();return 0;
goalFound: {
   if(parentCell!=goalCell)hierarchySetParent(goalCell,parentCell);
   m_isTunneling=false;
   Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)goalCell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
   rva002F40E7();goalCell->ReleaseInfo();goalCell->ReleaseInfo();*adjustedTo=adjustTo;return path;
  }
}
