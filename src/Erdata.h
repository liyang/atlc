/* Note, the number of dilectrics defined must be set by the parameter 
#define NUMBER_OF_DIELECTRICS_DEFINED ?? in definitions.h. There needs
ot be a better way of setting this, but for now it will do */

char *names[]={"Vacuum","Air","PTFE", "duroid_5880","Polyethelene", "Polystyrene", "PVC","Epoxy_resin", "Fibreglass_PCB", "duroid_6006","duroid_6010","one_hundred"};
double Ers[]={1.0,1.0006, 2.1,2.2,2.33,2.5,3.3,3.335,4.8,6.15,10.2,100.0};
int colours[]={0xffffff,0xffcaca, 0x8235ef,0x8e8e8e,0xff00ff,0xffff00,   0xefcc1a,0xbc7f60,0x1aefb3,0x696969,0xdcdcdc, 0xd5a04d};
