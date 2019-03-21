335CC Nicuta Loredana Ionela Tema 1 APD

	In realizarea acestei teme am implementat imaginea avand urmatoarele campuri:
		1. type : 2 caractere si reprezinta tipul pozei (P6 = color, P5 = black)
		2. height, width : dimensiunile pozei
		3. maxval : valoarea maxima a unui pixel
		4. pixel[][] : matrice de pixeli, avand campurile unsigned char R G B.
	!Atunci cand avem imagine de tip P5 vom folosi doar campul R din structura pixel.
	
	Pentru citire si scriere am folosit functiile fscanf/fprintf pentru tip si dimensiuni, 
respectiv fread si fwrite pentru datele fiecarui pixel.

	In homework.c in functia resize am verificat paritatea resize_factor-ului. 
		Daca este par atunci am luat submatricile de dimensiune resize_factor iar 
	pixelul din imaginea rezultata este media aritmetica a elementelor submatricii.
		Daca este impar atunci am extras submatricile de 3x3 elemente si am inmultit
	elemente cu element iar pixelul din imaginea rezultata este suma rezultatului
	inmultirii impartit la 16. (a durat pana cand mi-am dat seama ca problema e la 
	inmultire si ca se face element cu element si nu in mod obisnuit).
	!Am facut cazuri separate in functie de tip pentru a fi mai eficient si a nu evalua
	de fiecare data tipul fisierului pentru a vedea daca vor fi folosite si campurile
	G B.
	Scalabilitatea:
		Pentru verificarea scalabilitati nu am folosit cluster-ul, ci timpii locali
	verificand atat cu imputurile date in checker cat si cu imagini de dimensiuni mai mari
	obtinand urmatoarele rezultate:

		1. lenna_color cu res_factor= 2 : 1 thread ~ 0.003065
				 		  2 thread-uri ~ 0.002288
				 		  3 thread-uri ~ 0.001788
				 		  4 thread-uri ~ 0.001656

		2. lenna_bw cu res_factor= 2 : 1 thread ~ 0.001938
		              		       2 thread-uri ~ 0.001368
			      		       3 thread-uri ~ 0.001466
			      		       4 thread-uri ~ 0.001515

		3. Spaceship_color (5000 x 2813) cu res_factor = 2 : 1 thread ~ 0.153742
		              		      		       	     2 thread-uri ~ 0.087093
			      		     		       	     3 thread-uri ~ 0.064164
			      		       		             4 thread-uri ~ 0.052989

		4. Spaceship_bw (5000 x 2831) cu res_factor = 2 : 1 thread ~ 0.085154
		              		      		       	  2 thread-uri ~ 0.055452
			      		     		       	  3 thread-uri ~ 0.042169
			      		       		          4 thread-uri ~ 0.038415
		
		5. Galaxy_color (6149 x 2902) cu res_factor = 2 : 1 thread ~ 0.198021
		              		      		          2 thread-uri ~ 0.109392
			      		     		          3 thread-uri ~ 0.083136
			      		       		          4 thread-uri ~ 0.069253

		6. Galaxy_bw (6149 x 2902) cu res_factor = 2 : 1 thread ~ 0.115908
		              		      		       2 thread-uri ~ 0.069429
			      		     	               3 thread-uri ~ 0.063112
			      		       		       4 thread-uri ~ 0.047935

	In homework1.c in functia initialize am initializat imaginea ce are aceeasi structura
	precum imaginea de la punctul anterior doar ca avem un singur camp ce defineste culoarea
	deoarece imaginea este alb negru. Initial, imaginea este toata initializata cu culoarea
	alb.
	In functia render am parcurs toata matricea, am asignat coordonate specifice pentru
	a face translatarea din imagine in matrice (mi s-a parut mai usor sa gasesc o corelatie
	intre indecsii matricii si poza. Astfel un pixel[i][j] are in poza coordonatele
	(j, maxSize - i - 1) ). Am calculat distanta de la un pixel la ecutia dreptei 
	si am obtinut relatia |-x + 2y|/sqrt(5), iar daca aceasta este mai mica decat distanta
	maxima, atunci pixelul va fi colorat cu negru. (distanta maxima este 3 * resolution / 100
	deoarece am adaptat lungimea de 3cm pentru o rezolutie de 100cm noilor valori, prin metoda
	de 3 simpla).
	
	Scalabilitatea:
		Pentru verificarea scalabilitati nu am folosit cluster-ul, ci timpii locali
	verificand atat cu imputurile date in checker cat si cu imagini de dimensiuni mai mari
	obtinand urmatoarele rezultate:

		1. 1000 : 1 thread ~ 0.011797
		          2 thread-uri ~ 0.006476
			  3 thread-uri ~ 0.004352
			  4 thread-uri ~ 0.003541

		2. 8000 :  1 thread ~ 0.726561
		           2 thread-uri ~ 0.370104
			   3 thread-uri ~ 0.265572
			   4 thread-uri ~ 0.224584

		3. 10000 : 1 thread ~ 1.136167
		           2 thread-uri ~ 0.571999
			   3 thread-uri ~ 0.413120
			   4 thread-uri ~ 0.400848