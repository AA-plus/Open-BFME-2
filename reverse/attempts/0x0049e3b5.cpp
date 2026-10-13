// ?update@ProductionUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=1.0 date=2026-10-13
// cl: /I. /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii  /D_CRTIMP=
// stlport
#include "reverse/attempt_evidence/productionupdate/owner_context.inc"

// ZH update supplies the queue/door/unit/upgrade structure; BFME2/WB1204250
// supplies every added revival/companion/condition branch and observed offset.
UpdateSleepTime ProductionUpdate::update()
{
 static NameKeyType respawnKey=NAMEKEY("RespawnUpdate");
 const ProductionUpdateModuleData *d=getProductionUpdateModuleData();
 unsigned int now=TheGameLogic->getFrame();
 Object *us=getObject();
 void *experience=us->m_experience;
 rva0049E368();
 rva0049CF25();
 Rva0049D1B1 *production=const_cast<Rva0049D1B1 *>(GetEntryToProcess());
 if(us->getControllingPlayer()) {
  if(d->m_economyCondition) {
   if(((Rva002AE98B *)us->getControllingPlayer())->rva002AE98B(&d->m_economyKey)<0.0f) {
    us->setProductionCondition();
   } else us->clearProductionCondition();
  }
  if(d->m_economySound) {
   if(((Rva002AE98B *)us->getControllingPlayer())->rva002AE98B(&d->m_economyKey)<0.0f && !(us->m_flag438&1) && !us->testStatus((ObjectStatusTypes)2)) {
    if(!((ProductionAudioView *)TheAudio)->isPlaying(m_bfme12C)) {
     BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&d->m_economySound,us->m_id);
     ((Rva0033F15DDwordSlot *)&sound)->set(us->getControllingPlayer()->m_playerIndex);
     m_bfme12C=((ProductionAudioView *)TheAudio)->addEvent(&sound);
    }
   } else { ((ProductionAudioView *)TheAudio)->stopEvent(m_bfme12C); m_bfme12C=1; }
  }
 }
 if(d->m_numDoorAnimations>0) ((Rva0049D3BC *)this)->rva0049D3BC();
 if(m_bfme128>0) --m_bfme128;
 if(m_constructionCompleteFrame && now-m_constructionCompleteFrame>d->m_constructionCompleteDuration) {
  m_constructionCompleteFrame=0;
  m_clearFlags.set(74,true); m_setFlags.set(74,false); m_flagsDirty=true;
 }
 if(m_flagsDirty==true) { us->rva0028CFB2((const int *)&m_clearFlags,(const int *)&m_setFlags); m_clearFlags.clear(); m_setFlags.clear(); m_flagsDirty=false; }
 if(!production || us->testStatus((ObjectStatusTypes)19)) return UPDATE_SLEEP_NONE;
 Player *player=us->getControllingPlayer();
 if(!player) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
 if((production->m_type==PRODUCTION_UNIT || production->m_type==PRODUCTION_HORDE_UNIT) && m_bfme120==0 && m_bfme118<=0) {
  bool allowed=player->allowedToBuild(production->getProductionObject());
  bool available=((Rva002A7461 *)((char *)player+0x60))->rva002A7557((Rva002A7557In *)production->getProductionObject(),1);
  if((!allowed || !available) && !production->m_bfme34) {
   if(!available && player==((ProductionPlayerListView *)ThePlayerList)->localPlayer) TheEva->reportEvaEvent((EvaEventID)11,&us->m_position,0);
   return UPDATE_SLEEP_NONE;
  }
 }
 if(production->m_type==PRODUCTION_UPGRADE) {
  const UpgradeTemplate *upgrade=production->m_upgradeToResearch;
  if(upgrade && upgrade->getUpgradeType()==UPGRADE_TYPE_OBJECT && !getObject()->rva002940B9(upgrade)) { cancelUpgrade(upgrade); return UPDATE_SLEEP_NONE; }
 }
 ++production->m_bfme1C;
 int total=calcTotalProductionFrames((Rva0049CD4FArg *)production);
 production->m_percentComplete=(float)production->m_bfme1C/(float)total*100.0f;
 production->m_bfme18=100.0f/(float)total;
 bool ready=false;
 if(production->m_type==PRODUCTION_HORDE_UNIT && &player->m_revivalTracker) {
  int index=player->m_revivalTracker.rva0037EE4C(production->getProductionObject(),production->getProductionID(),0);
  float progress=((Rva0037E6E8 *)&player->m_revivalTracker)->rva0037E815(index,us);
  if(progress>=1.0f && m_bfme128==0) ready=true;
 } else if(production->m_percentComplete>=100.0f) ready=true;
 if(!ready) return UPDATE_SLEEP_NONE;
 switch(production->m_type) {
 case PRODUCTION_UNIT:
 case PRODUCTION_HORDE_UNIT: {
  bool revival=production->m_type==PRODUCTION_HORDE_UNIT;
  ExitInterface *exitInterface=us->getObjectExitInterface();
  if(exitInterface) {
  int numberToTry=production->m_productionQuantityTotal-production->m_productionQuantityProduced;
  for(int i=0;i<numberToTry;++i) {
   ExitDoorType exitDoor=production->m_exitDoor;
   if(production->m_objectToProduce && production->m_objectToProduce->productionSkipsDoor()) exitDoor=(ExitDoorType)-2;
   if(exitDoor==(ExitDoorType)-1) { exitDoor=exitInterface->reserveDoorForExit(production->m_objectToProduce,0); production->m_exitDoor=exitDoor; }
   if(exitDoor==(ExitDoorType)-1) continue;
   DoorInfo *door=(exitDoor>=0 && exitDoor<4)? &m_doors[exitDoor] : 0;
   if(d->m_numDoorAnimations>0 && door) {
    if(door->m_doorOpenedFrame==0 && door->m_doorWaitOpenFrame==0 && door->m_doorClosedFrame==0) {
     door->m_doorOpenedFrame=now; m_setFlags.set(ProductionDoorOpeningFlags[exitDoor]); m_flagsDirty=true;
    } else if(door->m_doorWaitOpenFrame!=0) door->m_doorWaitOpenFrame=now;
    else if(door->m_doorClosedFrame!=0) {
     door->m_doorWaitOpenFrame=now;
     m_clearFlags.set(ProductionDoorOpeningFlags[exitDoor],true); m_clearFlags.set(ProductionDoorClosingFlags[exitDoor],true);
     m_setFlags.set(ProductionDoorOpeningFlags[exitDoor],false); m_setFlags.set(ProductionDoorClosingFlags[exitDoor],false);
     m_setFlags.set(ProductionDoorWaitingOpenFlags[exitDoor]); m_flagsDirty=true;
    }
   }
   if(m_constructionCompleteFrame==0) { m_constructionCompleteFrame=now; m_setFlags.set(74); m_flagsDirty=true; }
   if(d->m_numDoorAnimations!=0 && door && door->m_doorWaitOpenFrame==0) continue;
   Object *newObj;
   if(m_bfme120==0) {
    Coord3D pos; pos.z=pos.y=pos.x=0.0f; float angle=0.0f;
    bool havePosition=exitInterface->getExitPosition(&pos,&angle);
    int revivalExperience=0;
    CreateMask mask;
    if(revival) {
     Player *controller=us->getControllingPlayer();
     UnitRevivalTracker *tracker=(UnitRevivalTracker *)&controller->m_revivalTracker;
     void *record=((Rva0037E421 *)tracker)->rva0037E451(production->m_productionID);
     if(record) revivalExperience=*(int *)((char *)record+0xc8);
     newObj=tracker->productionSystemNewObject(production->m_productionID,&pos);
     if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
     if(newObj->m_handle45C) TheGameLogic->rva0023D0C2(newObj,newObj->m_handle45C);
     else TheGameLogic->rva0023D0C2(newObj,us->m_handle45C);
     if(production->m_name!=AsciiString::TheEmptyString) {
      newObj->m_name=production->m_name;
      if(!((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(production->m_name) && !TheScriptEngine->didUnitExist(production->m_name)) TheScriptEngine->addObjectToCache(newObj,AsciiString(""));
      else TheScriptEngine->rva00357960(production->m_name,newObj);
     }
    } else {
     if(((ProductionAIView *)TheAI)->data->createdFlag) mask.bits[1]|=0x00800000;
     Team *team=us->getControllingPlayer()->m_defaultTeam;
     newObj=TheThingFactory->newObject(production->m_objectToProduce,team,&mask,false);
     if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; }
     if(production->m_name!=AsciiString::TheEmptyString) {
      newObj->m_name=production->m_name;
      if(!((Rva00358752Opaque *)TheScriptEngine)->lookupUnitByValue(production->m_name) && !TheScriptEngine->didUnitExist(production->m_name)) TheScriptEngine->addObjectToCache(newObj,AsciiString(""));
      else TheScriptEngine->rva00357960(production->m_name,newObj);
     }
     if(production->m_slave) {
      static NameKeyType slaveKey=NAMEKEY("SlaveWatcherBehavior");
      Module *watcher=getObject()->findUpdateModule(slaveKey);
      if(watcher) ((SlaveWatcherBehavior *)watcher)->rva00484869(newObj->m_id);
      for(BehaviorModule **m=newObj->getBehaviorModules();*m;++m) {
       ProductionSlaveInterface *slave=((ProductionBehaviorView *)((char *)*m+0xc))->getSlave();
       if(slave && getObject()) slave->setMaster(getObject());
      }
     }
     ((Rva0049CD24 *)this)->rva0049CD24(newObj);
     if(d->m_specialDuration>0) newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14a,d->m_specialDuration);
     newObj->m_bfme324=(float)production->m_cost;
     TheGameLogic->rva0023D0C2(newObj,us->m_handle45C);
    }
    m_bfme120=newObj->m_id; newObj->setProducer(us);
    if(((Thing *)newObj)->getDrawable() && us->getShroudStatusForPlayer(((ProductionPlayerListView *)ThePlayerList)->localPlayer->m_playerIndex)>=3) ((Thing *)newObj)->getDrawable()->setFullyObscuredByShroud(true);
    void *newExperience=newObj->m_experience;
    if(d->m_inheritVeterancy && newExperience && ((ProductionExperienceView *)experience)->level>=3) ((Rva003BD306Target *)newExperience)->rva0039B2C7(1,0);
    if(experience && !d->m_noExperience && ((Rva0039ADF3 *)experience)->rva0039AE04()) {
     int cost=production->m_objectToProduce->rva0033A69A(0,0,-1);
     if(cost>0) ((ExperienceTracker *)experience)->rva0039B315((float)cost,true,true,true,false);
    }
    if(havePosition) {
     ProductionAIUpdateView *ai=newObj->m_ai;
     if(ai && ai->s168()) {
      pos.z+=250.0f; newObj->teleportTo(&pos,true); ((Thing *)newObj)->setOrientation(angle);
     } else { ((Thing *)newObj)->setOrientation(angle); ((ProductionTerrainView *)TheTerrainLogic)->terrainHeight(pos.x,pos.y,&pos.z,0,0); newObj->teleportTo(&pos,true); }
    }
    const ThingTemplate *tmpl=newObj->m_template;
    newObj->setStatus((ObjectStatusTypes)0x5a,true);
    if(tmpl->m_buildVariationDuration>0.0f) {
     Coord3D rally; if(exitInterface->getNaturalRallyPoint(&rally,true)) ((ProductionAIView *)TheAI)->getPathfinder()->MoveAlliesAwayFromDestination(newObj,&us->m_position,&rally);
    }
    if(production->m_bfme30!=-1) {
     ((_STL::_Base_bitset<32> *)((char *)newObj+0x284))->_M_do_or((const _STL::_Base_bitset<32> &)Rva0028F633(0,production->m_bfme30));
    }
    newObj->updateUpgradeModules();
    Drawable *drawable=((Thing *)newObj)->getDrawable();
    drawable->rva000B3FD0(); ((Rva002707FA *)drawable)->rva002707FA(1);
    BfmeAudioEventPrefix136 voiceCreated(drawable->rva0049D114().ref,0);
    ((Rva002D9531 *)&voiceCreated)->rva002D9531(m_bfme120);
    ((Rva0033F15DDwordSlot *)&voiceCreated)->set(us->getControllingPlayer()->m_playerIndex);
    ((ProductionAudioView *)TheAudio)->addEvent(&voiceCreated);
    us->getControllingPlayer()->onUnitCreated(us,newObj);
    ((Rva0028CBFD *)newObj)->rva0028CBFD();
    if(production->m_productionQuantityTotal==production->m_productionQuantityTotal-production->m_productionQuantityProduced) {
     DrawableList list; list.push_back(drawable); Rva004D92FE info; info.drawTarget=((Thing *)us)->getDrawable();
     pickAndPlayUnitVoiceResponse(&list,(GameMessage::Type)0x7da,(PickAndPlayInfo *)&info);
    }
    rva0049DF81((Rva0049DF81Input *)production,newObj);
    float buildDuration=tmpl->m_buildVariationDuration;
    m_bfme118=(unsigned int)(buildDuration*(float)BfmeLogicFramesPerSecond);
    newObj->setSpecialModelConditionState((ModelConditionFlagType)0xda,m_bfme118);
    newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14d,5);
    newObj->setDisabledUntil((DisabledType)3,TheGameLogic->getFrame()+m_bfme118);
    if(!revival) { Drawable *draw=((Thing *)newObj)->getDrawable(); if(draw) { drawable->rva002723C0(m_bfme118); draw->rva00274176(true); } }
    const _STL::vector<AsciiString> &names=tmpl->m_auxiliaryTemplates;
    if(!names.empty()) {
     for(_STL::vector<AsciiString>::const_iterator it=names.begin();it!=names.end();++it) {
      const ThingTemplate *extraTemplate=TheThingFactory->findTemplate(*it); if(!extraTemplate) continue;
      Team *team=us->getControllingPlayer()->m_defaultTeam;
      Object *extra=TheThingFactory->newObject(extraTemplate,team,&mask,false);
      ((Rva0049CD24 *)this)->rva0049CD24(extra);
      if(exitInterface->getExitPosition(&pos,&angle)) { ((Thing *)extra)->setPosition(&pos); ((Thing *)extra)->setOrientation(angle); }
      ((Thing *)extra)->getDrawable()->setDrawableHidden(true);
      if(!extra->m_modelConditionFlags.test(218)) { extra->m_modelConditionFlags.set(218); extra->rva0028AE6D(); }
      newObj->setSpecialModelConditionState((ModelConditionFlagType)0x14d,5);
      ObjectID id=extra->m_id; m_createdAuxiliary.push_back(id);
     }
     m_bfme11C=false;
    }
    Module *respawn=newObj->findUpdateModule(respawnKey);
    if(revival && respawn) { ((RespawnUpdate *)respawn)->triggerRevival(us); if(newObj->m_experience) ((ProductionExperienceView *)newObj->m_experience)->next=revivalExperience;
     m_bfme128=4*BfmeLogicFramesPerSecond; newObj->rva002900FA(TheGameLogic->getFrame()+4*BfmeLogicFramesPerSecond); }
   } else { newObj=TheGameLogic->findObjectByID(m_bfme120); if(!newObj) { removeFromProductionQueue(production); ::delete production; return UPDATE_SLEEP_NONE; } }
   ProductionContainView *contain=newObj->m_contain;
   ProductionHordeInterface *horde=contain ? contain->getHorde() : 0;
   if(horde) { const ThingTemplate *tmpl=TheThingFactory->findTemplate(horde->getTemplateName()); int extraCount=horde->getExtraCount();
    if(tmpl) { ++extraCount; production->m_cost=0; production->m_objectToProduce=tmpl; production->m_productionQuantityTotal=extraCount; production->m_bfme34=true; } }
   if(!m_bfme11C) {
    float duration=getObject()->m_template->m_buildVariationDuration;
    if(!m_createdAuxiliary.empty()) for(_STL::list<ObjectID>::iterator it=m_createdAuxiliary.begin();it!=m_createdAuxiliary.end();++it) {
     Object *extra=TheGameLogic->findObjectByID(*it); if(!extra) continue;
     ((Thing *)extra)->getDrawable()->setDrawableHidden(false); ((Thing *)extra)->getDrawable()->rva000B3FD0();
     ((Thing *)extra)->getDrawable()->fadeIn((unsigned int)(BfmeClientFramesPerSecond*duration));
    }
    m_bfme11C=true;
   }
   if(m_bfme118) { --m_bfme118; return UPDATE_SLEEP_NONE; }
   if(newObj->m_modelConditionFlags.test(218)) { newObj->m_modelConditionFlags.set(218,false); newObj->rva0028AE6D(); }
   if(d->m_completeDuration>0) newObj->setSpecialModelConditionState((ModelConditionFlagType)0x5f,d->m_completeDuration);
   if(newObj->isKindOf((KindOfType)0xda)) newObj->clearDisabled((DisabledType)3);
   m_bfme120=(ObjectID)0;
   if(!newObj->findUpdateModule(respawnKey)) exitInterface->exitObjectViaDoor(newObj,exitDoor);
   ++production->m_productionQuantityProduced; production->m_exitDoor=(ExitDoorType)-1;
   if(production->m_productionQuantityTotal-production->m_productionQuantityProduced==0) {
    Object *container=TheGameLogic->findObjectByID(newObj->m_containerID);
    if(container) { ProductionContainView *containerInterface=container->m_contain;
    if(containerInterface) {
     ProductionAIUpdateView *hordeAI=containerInterface->getAI();
     if(hordeAI) { DrawableList list; Drawable *draw=((Thing *)container)->getDrawable(); list.push_back(draw);
      Rva004D92FE info; info.drawTarget=((Thing *)us)->getDrawable(); pickAndPlayUnitVoiceResponse(&list,(GameMessage::Type)0x7e2,(PickAndPlayInfo *)&info);
      hordeAI->s234(us); }
    } }
   }
  }
  if(production->m_productionQuantityTotal-production->m_productionQuantityProduced==0) { removeFromProductionQueue(production); ::delete production; exitInterface->exitSlot11(); }
  } else { removeFromProductionQueue(production); ::delete production; }
  break;
 }
 case PRODUCTION_UPGRADE: {
  const UpgradeTemplate *upgrade=production->m_upgradeToResearch;
  if(experience && !d->m_noExperience && ((Rva0039ADF3 *)experience)->rva0039AE04()) { int cost=upgrade->rva0026EF50(0,0); if(cost>0) ((ExperienceTracker *)experience)->rva0039B315((float)cost,true,true,true,false); }
  ObjectID producerID=us->m_id;
  int producerPlayer=us->getControllingPlayer()->m_playerIndex;
  TheScriptEngine->rva00357F11(producerPlayer,upgrade->getUpgradeName(),producerID);
  if(us->isLocallyControlled()) {
   UnicodeString message; UnicodeString format=TheGameText->fetch("UPGRADE:UpgradeComplete"); UnicodeString name=TheGameText->fetch(upgrade->m_displayName.str());
   message.format(format.str(),name.str()); ((ProductionInGameUIView *)TheInGameUI)->message(message);
   TheRadar->createEvent(&us->m_position,(RadarEventType)2,4.0f);
   bool sounded=false;
   if(upgrade->m_evaEvent!=-1) { TheEva->reportEvaEvent((EvaEventID)upgrade->m_evaEvent,&us->m_position,0); sounded=true; }
   if(upgrade->m_researchSound) { BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&upgrade->m_researchSound,0); ((Rva002D9531 *)&sound)->rva002D9531(us->m_id); ((ProductionAudioView *)TheAudio)->addEvent(&sound); sounded=true; }
   if(!sounded) TheEva->reportEvaEvent((EvaEventID)4,&us->m_position,0);
   BfmeAudioEventPrefix136 sound(*(const OpaqueRefElement4 *)&upgrade->m_unitSound,0); ((Rva002D9531 *)&sound)->rva002D9531(us->m_id); ((ProductionAudioView *)TheAudio)->addEvent(&sound);
  }
  if(!((Rva004DC8E7AsciiField *)upgrade)->get().isEmpty()) {
   const FXList *fx=TheFXListStore->findFXList(((Rva004DC8E7AsciiField *)upgrade)->get().str()); if(fx) FXList::doFXObj(fx,us,0);
  }
  if(upgrade->getUpgradeType()==UPGRADE_TYPE_PLAYER) player->rva002AE329(upgrade,(UpgradeStatusType)2,0); else us->rva00293077(upgrade);
  Drawable *draw=((ProductionInGameUIView *)TheInGameUI)->getSelectedDrawable(); Object *selected=draw ? ((ProductionDrawableView *)draw)->object : 0;
  if(selected) { const ThingTemplate *selectedTemplate=selected->getTemplate(); for(int i=0;i<5;++i) if(TheUpgradeCenter->findUpgrade(selectedTemplate->upgradeCameos()[i])==upgrade) { ((ProductionControlBarView *)TheControlBar)->dirty=true; break; } }
  removeFromProductionQueue(production); ::delete production; m_bfme120=(ObjectID)0;
  break;
 }
 }
 return UPDATE_SLEEP_NONE;
}
