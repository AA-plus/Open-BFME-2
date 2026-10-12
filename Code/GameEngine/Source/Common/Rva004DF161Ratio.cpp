// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?getEnergySupplyRatio@Energy@@QBEMXZ, RVA 0x004DF161, 30 bytes.
// WorldBuilder names it Energy::getEnergySupplyRatio (ZH: production over
// consumption, 1.0 with no consumption); Energy keeps production at +4 and
// consumption at +8 (EnergyAdjustPower.cpp).
// Float ratio: returns 1.0f when m_08 is zero else (float)m_04/(float)m_08.
// Evidence: fld 1.0f at 0x007BB8D8 plus fild [ecx+4] plus fidiv [ebp-4];
// callers at 0x0033AAAC 0x003E46FB use result as float; same 1.0f pool as 0x0039DA2A.
class Energy
{
public:
	float getEnergySupplyRatio() const;
	int m_00;
	int m_energyProduction;
	int m_energyConsumption;
};

float Energy::getEnergySupplyRatio() const
{
	int consumption = m_energyConsumption;
	if (consumption == 0)
		return 1.0f;
	return (float)m_energyProduction / (float)consumption;
}
