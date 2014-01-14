struct nvg{

	int tab[2500];
	int m;
	int n;
};

struct histogr{

	int tab[255];
};
	
program TP6{

	version HISTOVERS{
	
		histogr HISTO(nvg) = 1;
		nvg  MOY(nvg) = 2;
		nvg  MED(nvg) = 3;
	}= 1;
	
}=0x30000021;
