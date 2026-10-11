// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Named scalar globals that retail keeps in .data and the ledger listed as unowned, so every unit
// that reads one had an unresolved name. Initial values are read from the image.
int nShadowStartBatchVertex = 0;		// retail 0x009EBCE8
int nShadowStartBatchIndex = 0;		// retail 0x009EBCF0
float beZ = 0.0f;		// retail 0x009EBCC0
float beY = 0.0f;		// retail 0x009EBCC4
float beX = 0.0f;		// retail 0x009EBCC8
float bcZ = 0.0f;		// retail 0x009EBCCC
float bcY = 0.0f;		// retail 0x009EBCD0
float bcX = 0.0f;		// retail 0x009EBCD4
int matchbotProfileID = 0;		// retail 0x00A02698
float Rva00783F90Red = 0.0f;		// retail 0x009E6188
float Rva00783F90Green = 0.0f;		// retail 0x009E618C
float Rva00783F90Blue = 0.0f;		// retail 0x009E6190
int LANGameOptionsRetries = 0;		// retail 0x009FE95C
bool AssetInitRunTextureBuilder = true;		// retail 0x009B61E8
bool AssetInitRunModelBuilder = true;		// retail 0x009B61E9
