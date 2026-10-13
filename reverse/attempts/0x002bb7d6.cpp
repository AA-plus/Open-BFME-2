// ?Update@Rva002B74DE@@QAEHXZ
// partial score=0.979 date=2026-10-13
// ?Update@Rva002B74DE@@QAEHXZ
// partial score=0.979 date=2026-10-13
// Retail 0x002BB7D6 (623B). Home-ported to LivingWorldLogic.cpp (proper home:
// rowed ctor/dtor, /EHs flags, all callees rowed, 117/117 green) compiles 580B.
// Head exact through winner-check; walls (all allocator/scheduling):
// (1) null-check: retail cmp [edi],0 immediate; every spelling tried pins a
//     zero reg (holder->get/m_ptr/getRef/volatile all load+test or xor+cmp).
//     Retail reuses edi (holder-addr, dies after transfer) as zero LATE, so
//     null-check (early, edi live) uses immediate. Mine hoists ebx-zero early
//     covering null-check + EH/index. Next: kill the early hoist (make later
//     zeros use edi by freeing it sooner?) or force immediate.
// (2) transfer 6B: retail edx=esp then null then store; mine null then eax=esp.
// (3) SIB x2: retail base=offset/index=base ([ebx+ecx]); mine conventional.
//     Try commuted address arithmetic.
// (4) winner order: retail loads result-home then owned-home; mine swapped.
// Infra KEPT in LivingWorldLogic.cpp (build-green): Rva002B6126Listener
// slot04/slot08, Rva002B2EC7::get, LivingWorldBattle sides()/Compute...,
// all helper views, public Rva002B4326::m_ptr. Method reverted below.
// t=35 model=muse-spark
Int Rva002B74DE::Update()
{
	if (*(Rva004FA2E2 *volatile *)&m_holder0C.m_ptr) {
		if (!((Rva002B466E *)this)->rva002B466E())
			return 0;
		if (((ResolverSimHeader *)m_holder0C.get())->winner() == -1) {
			Bool fast = ((Rva002B471B *)this)->rva002B471B();
			for (;;) {
				((Rva004FA10FOwner *)m_holder0C.get())->rva004FA10F();
				Rva004FA2E2 *sim = m_holder0C.get();
				((Rva002B6126List *)((char *)m_logic + 0x2c))->forEach(&Rva002B6126Listener::slot04, m_logic, m_battle, (int)sim);
				if (((ResolverSimHeader *)m_holder0C.get())->winner() != -1)
					break;
				fast = fast || ((Rva002B471B *)this)->rva002B471B();
				if (!fast && !((Rva002B466E *)this)->rva002B466E())
					return 0;
			}
		}
		Rva002B43E7 owned(((Rva002B54BB *)&m_holder0C)->rva002B54BB().transfer());
		((LivingWorldAutoResolveBattle *)owned.m_ptr)->applyResults();
		ResolverSimHeader *result = (ResolverSimHeader *)owned.m_ptr;
		int index = 0;
		for (int side = 0; side < ((LivingWorldBattle *)m_battle)->sides(); ++side) {
			int count = ((Rva003F468D *)m_battle)->rva003F4DAE(side);
			for (int army = 0; army < count; ++army, ++index) {
				ResolverArmyView *a = (ResolverArmyView *)((Rva003F468D *)m_battle)->rva003F468D(side, army);
				a->value1c8 = ((ResolverUnit2B74DE *)m_holder08.get())[index].getValue();
				((Rva002E062EDwordSlot *)a)->set(((ResolverUnit2B74DE *)m_holder08.get())[index].getCount() - ((Rva004E05E9DwordField *)a)->get());
			}
		}
		index = 0;
		for (int side = 0; side < ((LivingWorldBattle *)m_battle)->sides(); ++side) {
			Bool found = false;
			int count = ((Rva003F468D *)m_battle)->rva003F4DAE(side);
			for (int army = 0; army < count; ++army, ++index) {
				if (((ResolverPlayerRecord *)result->players)[index].isSide(((ResolverSimHeader *)owned.m_ptr)->winner())) {
					if (!found) {
						((LivingWorldBattle *)m_battle)->m_side = side;
						found = true;
					}
				} else {
					struct Rva002B89BBInfo *a = (struct Rva002B89BBInfo *)((Rva003F468D *)m_battle)->rva003F468D(side, army);
					m_logic->rva002B3833((LivingWorldBattle *)m_battle, a);
				}
			}
		}
		((LivingWorldBattle *)m_battle)->ComputeBattleResultsForPlayersAfterAutoBattle((Rva003F4E07Results *)owned.m_ptr);
		m_logic->OnBattleComplete((LivingWorldBattle *)m_battle);
		((Rva002B6126List *)((char *)m_logic + 0x2c))->forEach(&Rva002B6126Listener::slot08, m_logic, m_battle, (int)owned.m_ptr);
		((LivingWorldRegionManager *)*(void **)((char *)m_logic + 0xb0))->rva0020FB8B((LivingWorldBattle *)m_battle);
	}
	return 1;
}
