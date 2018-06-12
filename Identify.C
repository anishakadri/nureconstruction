
int id_0pi(vector<Particle> PartVec){
	int counter = 0;

	for (unsigned int i=0;i<PartVec.size();i++){
    	Particle Part = PartVec[i];
    	int pdg = Part.GetPDG();

	if (pdg == 2212){
	        counter++;
	}
	
    	if (abs(pdg) == 211){
    		counter+=2;
    	}

    	if (abs(pdg)== 111){
    		counter+=2;
    	}
	if (abs(pdg)== 3122){ //lambda
    		counter+=2;
    	}
	if (abs(pdg)== 221){ //eta
    		counter+=2;
    	}
	if (abs(pdg)== 321){ //K+/-
	        counter+=2;
    	}
	if (abs(pdg)== 130){ //K0(S)
    		counter+=2;
    	}
	if (abs(pdg)== 310){ //K0(L)
    		counter+=2;
    	}
		
    }
    
    if (counter == 1){
    	return 1;
    }else {
    	   return 0;
        }

}

int id_1pi(vector<Particle> PartVec){
	int counter = 0;

	for (unsigned int i=0;i<PartVec.size();i++){
    	Particle Part = PartVec[i];
    	int pdg = Part.GetPDG();

    	if (pdg == 211){
    		counter++;
    	}
	if (pdg == -211){
	        counter+=2;
	}
	if (abs(pdg)== 111){
    		counter+=2;
    	}
	if (abs(pdg)== 3122){ //lambda
    		counter+=2;
    	}
	if (abs(pdg)== 221){ //eta
    		counter+=2;
    	}
	if (abs(pdg)== 321){ //K+/-
    		counter+=2;
    	}
	if (abs(pdg)== 130){ //K0(S)
    		counter+=2;
    	}
	if (abs(pdg)== 310){ //K0(L)
    		counter+=2;
    	}

    }
    
    if (counter == 1){
    	return 1;
    }else {
    	return 0;
        }
        
}
