/*********************************************
 * OPL 12.9.0.0 Model
 * Author: polaris
 * Creation Date: 2021年4月7日 at 下午10:46:57
 *********************************************/
 
int NbMonths = ...;
int NbProds = ...;
int NbMachines = ...;

range month = 1..NbMonths;
range month_add_zero = 0..NbMonths;
range product = 1..NbProds;
range machine = 1..NbMachines;


int ProfitProd[product] = ...;
float ProcessProd[machine][product] = ...;
int MarketProd[month][product] = ...;
float CostHold = ...;
int StartHold = ...;
int EndHold = ...;
int MaxHold = ...;
int HoursMonth = ...;
int NumProcess[machine] = ...;

dvar int x[month][product];				
dvar int y[month_add_zero][product];	
dvar int z[month][product];				
dvar int w[month][machine];				

dvar float SP;							
dvar float HC;							
dvar float NP;							

maximize NP;

subject to{
	forall(i in month)
	  forall(j in product)
	    x[i][j] >= 0 && y[i][j] >= 0 && z[i][j] >= 0;	
	    
	forall(i in month)
	  forall(j in machine)
	    w[i][j] >= 0;
	    
	forall(j in product)
	  y[0][j] == StartHold && y[NbMonths][j] == EndHold;	   
	  
	forall(i in month)
	  forall(j in product)
	    y[i][j] <= MaxHold;
	    
	forall(j in machine)
	  (sum(i in month) w[i][j]) == NumProcess[j];
	  
	forall(i in month)
	  forall(j in product)
	    z[i][j] == y[i-1][j] + x[i][j] - y[i][j];
	
	forall(i in month)
	  forall(j in product)
	    z[i][j] <= MarketProd[i][j];
	
	forall(i in month)
	  forall(k in machine)
	    (sum(j in product) ProcessProd[k][j]*x[i][j]) <= HoursMonth*(NumProcess[k] - w[i][k]);
	    
	SP == (sum(j in product) ProfitProd[j] * (sum(i in month)z[i][j]));
	HC == CostHold * (sum(i in month) (sum(j in product) y[i][j]));
	NP == SP-HC;
}

execute{
	write("The month for maintenance:\n\t"); 
	writeln(w);
	write("The amount to make in each month:\n\t"); 
	writeln(x);
	write("The amount to hold at the end of each month:\n\t"); 
	writeln(y);
	write("The amount to sell in each month:\n\t"); 
	writeln(z);
	
	write("Total Sell Profit = "); 
	writeln(SP);
	write("Total Holding Cost = "); 
	writeln(HC);
	write("Total Net Profit = "); 
	writeln(NP);
}	