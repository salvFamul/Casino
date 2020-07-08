#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum{
    true=0,false
}bool;

typedef struct utente{		//struct che memorizza le informazioni sull'utente registrato
    char nome[21];
    char cognome[21];
    char nickname[21];
    char password[21];
    char codice[17];
    bool admin;
    bool online;
    int seduto;	//questo intero vale 0 se l'utente non risulta seduto a un tavolo, altrimenti vale quanto il numero identificativo del tavolo a cui e' seduto
    float saldo;
}utente;

typedef struct tavolo{
    int num;
    int persone;
    struct l_nickname* testa;
}tavolo;

typedef struct tipo_gioco{
    char nome[21];
    int giocatori_min;
    int giocatori_max;
    struct l_tavoli* testa;
}tipo_gioco;


typedef struct l_nickname{
    char nick[21];
    struct l_nickname* next;
}l_nickname;


typedef struct l_utenti{
    struct utente user;
    struct l_utenti* next;
}l_utenti;

typedef struct l_giochi{
    struct tipo_gioco gioco;
    struct l_giochi* next;
}l_giochi;

typedef struct l_tavoli{
    struct tavolo t;
    struct l_tavoli* next;
}l_tavoli;

void inserisciTesta_utenti(l_utenti** testa, utente u);
void inserisciTesta_giochi(l_giochi** testa, tipo_gioco g);
void inserisciTesta_tavoli(l_tavoli** testa, tavolo t);
void inserisciTesta_nickname(l_nickname** testa, char nick[]);
utente popUtenti(l_utenti** top);
tipo_gioco popGiochi(l_giochi** top);
tavolo popTavoli(l_tavoli** top);
void inserisciOrdin_utenti(l_utenti** testa, utente u);
void inserisciOrdin_giochi(l_giochi** testa, tipo_gioco g);
void inserisciOrdin_tavoli(l_tavoli** testa, tavolo t);
bool tavoloInseribile(l_giochi* testa, int numTavolo, char giocoTavolo[21]);
l_tavoli** cercaLista_tavoli(l_giochi* testa, char giocoTavolo[21]);
//l_tavoli* cercaNum_tavolo(l_giochi* testa, int numTavolo);
void inserisciOrdin_nickname(l_nickname** testa, char nick[21]);
void stampaUtenti(l_utenti *testa);
void stampaGiochi(l_giochi *testa);
void stampaNickname(l_nickname *testa);
void stampaTavoli(l_giochi *testa);
void cancellaUtente(l_utenti** testa, char nick[],utente u);
void cancellaNick(l_nickname** testa, char nick[]);
void svuotaNick(l_nickname** testa, l_utenti* testa_u);
void svuotaTavoli(l_tavoli** testa, l_utenti* testa_u);
void cancellaTavolo(l_giochi** testa, l_utenti* testa_u, int num);
void cancellaGioco(l_giochi** testa, l_utenti* testa_u, char gioco[]);
void aggiornaSaldo(l_utenti* testa, char str[]);
void iniziaPartita(l_giochi* testa_g, l_utenti* testa_u, int numTavolo);
void lasciaTavolo(l_giochi** testa,utente u);
int login(l_utenti *testa, utente u, l_giochi** testa_giochi, utente** u2);
void gestioneClienti(l_utenti** lista_u, int scelta, utente u);
void gestioneGiochi(l_giochi** lista_g, l_utenti** lista_u, int scelta);
void gestioneTavoli(l_giochi** lista_g, l_utenti** lista_u, int scelta);
void sottoMenu(l_giochi** lista_g, l_utenti** lista_u, int scelta, utente u);
void menuAdmin(l_giochi** lista_g, l_utenti** lista_u, utente* u);
bool siediti(l_giochi** testa, int numTavolo, utente** u);
void menuUtente(l_giochi** lista_g, utente* u);
void menu(l_giochi** lista_g, l_utenti** lista_u);
void salva(l_giochi* testa_g, l_utenti* testa_u);
void inizializza(l_giochi** lista_g,l_utenti** lista_u);
void start();




int main(){
	
	start();
	
}







void inserisciTesta_utenti(l_utenti** testa, utente u){
    l_utenti* p=NULL;
    p=(l_utenti*)malloc(sizeof(l_utenti));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }
    p->user=u;
    p->next=*testa;
    *testa=p;
    return;
}
void inserisciTesta_giochi(l_giochi** testa, tipo_gioco g){
    l_giochi* p=NULL;
    p=(l_giochi*)malloc(sizeof(l_giochi));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }
    p->gioco=g;
    p->next=*testa;
    *testa=p;
    return;
}

void inserisciTesta_tavoli(l_tavoli** testa, tavolo t){
    l_tavoli* p=NULL;
    p=(l_tavoli*)malloc(sizeof(l_tavoli));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }
    p->t=t;
    p->next=*testa;
    *testa=p;
    return;
}

void inserisciTesta_nickname(l_nickname** testa, char nick[]){
    l_nickname* p=NULL;
    p=(l_nickname*)malloc(sizeof(l_nickname));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }
    strcpy(p->nick,nick);
    p->next=*testa;
    *testa=p;
    return;
}

utente popUtenti(l_utenti** top){	//funzione pop per pila di appoggio da usare durante lettura da file
	
	utente u;
	l_utenti* p;
	
	u=(*top)->user;
	p=*top;
	*top=(*top)->next;
	free(p);
	
	return u;
		
}

tipo_gioco popGiochi(l_giochi** top){	//funzione pop per pila di appoggio da usare durante lettura da file
	
	tipo_gioco g;
	l_giochi* p;
	
	g=(*top)->gioco;
	p=*top;
	*top=(*top)->next;
	free(p);
	
	return g;
		
}

tavolo popTavoli(l_tavoli** top){		//funzione pop per pila di appoggio da usare durante lettura da file
	
	tavolo t;
	l_tavoli* p;
	
	t=(*top)->t;
	p=*top;
	*top=(*top)->next;
	free(p);
	
	return t;
		
}



void inserisciOrdin_utenti(l_utenti** testa, utente u){
    l_utenti* p=NULL,*q=*testa,*s=*testa;


    while((s!=NULL)&&((strcmp(u.nickname,s->user.nickname))>=0)){
      q=s;
      s=s->next;
    }
    
        if((q!=NULL)&&((strcmp(u.nickname,q->user.nickname))==0)){
    	printf("Impossibile avere due utenti con lo stesso nickname\n");
    	return;
	}
    
    if(s==*testa){
      inserisciTesta_utenti(testa,u);
      printf("Registrazione avvenuta con successo\n");
      return;
    }

    p=(l_utenti*)malloc(sizeof(l_utenti));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }

    p->user=u;

    q->next=p;
    p->next=s;
	
	printf("Registrazione avvenuta con successo\n");
	
    return;
}

void inserisciOrdin_giochi(l_giochi** testa, tipo_gioco g){
    l_giochi* p=NULL,*q=*testa,*s=*testa;


	

    while((s!=NULL)&&((strcmp(g.nome,s->gioco.nome))>=0)){
      q=s;
      s=s->next;
    }
    
    if((q!=NULL)&&((strcmp(g.nome,q->gioco.nome))==0)){
    	printf("Impossibile avere due giochi con lo stesso nome\n");
    	return;
	}
    
   
    if(s==*testa){
      inserisciTesta_giochi(testa,g);
      printf("\nInserimento gioco avvenuto con successo\n");
      return;
    }

    p=(l_giochi*)malloc(sizeof(l_giochi));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }

    p->gioco=g;

    q->next=p;
    p->next=s;
	
	printf("\nInserimento gioco avvenuto con successo\n");
	
    return;
}


void inserisciOrdin_tavoli(l_tavoli** testa, tavolo t){
   
    l_tavoli* p=NULL,*q=*testa,*s=*testa;
	
    


    while((s!=NULL)&&(t.num>=s->t.num)){
      q=s;
      s=s->next;
    }
    
    if((q!=NULL)&&(t.num==q->t.num)){
    	printf("Impossibile avere due tavoli con lo stesso numero\n");
    	return;
	}
    
        
    if(s==*testa){
      inserisciTesta_tavoli(testa,t);
      printf("Inserimento avvenuto correttamente");
      return;
    }
    

    p=(l_tavoli*)malloc(sizeof(l_tavoli));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }

    p->t=t;

    q->next=p;
    p->next=s;
	
	printf("Inserimento tavolo avvenuto con successo");
	
    return;
}

bool tavoloInseribile(l_giochi* testa, int numTavolo, char giocoTavolo[21]){	//verifica disponibilita' del tavolo che si vuole inserire e correttezza del nome del gioco a cui il tavolo va dedicato
   
    l_giochi *s=testa;
    l_tavoli* p=NULL;
	bool nomeTrovato=false;
    
	if(numTavolo<=0)		//non e' possibile provare a inserire un tavolo di numero identificativo negativo o nullo
		return false;
	
    while(s!=NULL){ //scorre la lista giochi e controlla se il nome e' corretto
      
      if(strcmp(s->gioco.nome,giocoTavolo)==0){
      	
      	nomeTrovato=true;	//il nome del gioco a cui si vuole adibire il tavolo e' presente nella lista, ma si
      						//deve ancora scorrere tutta la lista di giochi per vedere se il numero identificativo del tavolo
      						//da aggiungere non sia gia' presente
      	
	  }
	  p=s->gioco.testa;
	  s=s->next;
      
      while(p!=NULL){	//controlla se il numero e' gia' presente in questa lista
    
    	if(p->t.num==numTavolo){
    		printf("Esiste gia' un tavolo con questo numero\n");
    		return false;	//se viene trovato un tavolo con il numero desiderato, l'inserimento e' impossibile e la funzione esce subito restituendo 1
    	}
		p=p->next;
	  	}
	}
		
    /*if((tavoloTrovato==false)&&(nomeTrovato==true)){
    	
    		
    	return true;
	}*/
	
	
	//se il programma e' arrivato fino a qui, vuol dire sicuramente che si puo' inserire un tavolo con il numero indicato
	//la possibilita' di procedere all'inserimento e' data solo dalla correttezza del nome del gioco a cui destinare il tavolo
	
	return nomeTrovato;
   		
	            
}

l_tavoli** cercaLista_tavoli(l_giochi* testa, char giocoTavolo[21]){ 		//restituisce l'indirizzo del puntatore alla lista di tavoli del gioco desiderato
   
    l_giochi *s=testa;
    l_tavoli* p=NULL,*q=p;
	
    

	
    while(s!=NULL){ 
    	if(strcmp(s->gioco.nome,giocoTavolo)==0)		//scorre la lista di giochi fino a quando non trova il nodo con il nome voluto
    		return &(s->gioco.testa);					//una volta trovato il nodo, si restituisce il puntatore doppio alla lista di tavoli annessa
    	s=s->next;
	}
	
	return NULL;
     
    //si presuppone che questa funzione venga chiamata sempre previo controllo della disponibilita' del tavolo (tramite apposita funzione)
    //per questo motivo si e' sempre certi di trovare il nodo desiderato e non ci sono particolari condizioni di uscita anticipata dal ciclo di ricerca
}

/*
l_tavoli* cercaNum_tavolo(l_giochi* testa, int numTavolo){ //restituisce il puntatore ad una delle liste di tavoli se il tavolo e' presente in una delle liste
															 //altrimenti restituisce NULL
   
    l_giochi *s=testa;
    l_tavoli* p;
	
    


    while(s!=NULL){ 
      p=s->gioco.testa;
      s=s->next;
      
      while(p!=NULL){	//controlla se il numero e' presente
      	
      	if(p->t.num==numTavolo)
      		return p;
		p=p->next;
      	
	  }
	}
	 return NULL;
    
    
}
*/





void inserisciOrdin_nickname(l_nickname** testa, char nick[21]){
    l_nickname* p=NULL,*q=*testa,*s=*testa;
	



    while((s!=NULL)&&((strcmp(nick,s->nick))>=0)){
      
	  q=s;
      s=s->next;
    }

    if((s==*testa)){
      inserisciTesta_nickname(testa,nick);
      return;
    }

    p=(l_nickname*)malloc(sizeof(l_nickname));
    if(p==NULL){
        printf("Errore nell'allocazione della memoria");
        return;
    }

    strcpy(p->nick,nick);

    q->next=p;
 
    p->next=s;

}



void stampaUtenti(l_utenti *testa){
	l_utenti* temp=testa;
	
	if(temp==NULL){
		printf("Lista utenti vuota\n");
		return;
	}
		
	while(temp!=NULL){
		printf("%s %s\t",temp->user.nome,temp->user.cognome);	
		printf("Nickname: %s\t",temp->user.nickname);
		if(temp->user.online==true)
			if(temp->user.admin==true)
				printf("Stato: online\t");
			else{
				if(temp->user.seduto==0)
					printf("Stato: inattivo\t");
				else{
					printf("Stato: online\t");
				}
			}
			
		else
			printf("Stato: offline\t");
		if(temp->user.admin==true)
			printf("Admin\n");
		else
			printf("Utente\n");
		
		temp=temp->next;
	}	
	return;
}

void stampaGiochi(l_giochi *testa){
	l_giochi* temp=testa;
	
	if(temp==NULL){
		printf("Lista vuota\n");
		return;
	}
		
	while(temp!=NULL){
		printf("%s\t\tGiocatori min: %d\tGiocatori max: %d\n",temp->gioco.nome,temp->gioco.giocatori_min,temp->gioco.giocatori_max);
		temp=temp->next;
		
	}	
	
}
/*
void stampaNickname(l_nickname *testa){
	l_nickname* temp=testa;
	
	if(temp==NULL){
		printf("Lista vuota\n");
		return;
	}
		
	while(temp!=NULL){
		printf("%t%s\n",temp->nick);
		temp=temp->next;
	}	
	
}*/

void stampaTavoli(l_giochi *testa){
	l_giochi* temp1=testa;
	l_tavoli* temp2;
	l_nickname* temp3;
	
	if(temp1==NULL){
		printf("La lista dei giochi e' vuota\n");
		return;
	}
	
	do{
		printf("Lista tavoli %s:\n",temp1->gioco.nome);		//scorre la lista dei giochi 
		temp2=temp1->gioco.testa;		
		if(temp2==NULL){
			printf("La lista dei tavoli per questo gioco e' vuota\n");
		}
		else{
			do{		//scorre la lista dei tavoli per ogni gioco
				printf("\tTavolo numero %d\n",temp2->t.num);
				temp3=temp2->t.testa;
				if(temp3==NULL){
					printf("\tIl tavolo e' vuoto\n\n");
				}
				else{
					printf("\tPersone sedute:\n");
					do{		//scorre la lista di persone sedute per ogni tavolo
						printf("\t\t%s\n",temp3->nick);
						temp3=temp3->next;
					}while(temp3!=NULL);
				}
				temp2=temp2->next;
			}while(temp2!=NULL);
		}
		temp1=temp1->next;
		
	}while(temp1!=NULL);
	
	
	return;
}

void cancellaUtente(l_utenti** testa, char nick[],utente u){
	l_utenti* q=*testa,*s=*testa;
	while((s!=NULL)&&(strcmp(s->user.nickname,nick)!=0)){
		
		if(strcmp(s->user.nickname,nick)>0){
			printf("Nessun utente con questo nome\n");	//se la lista e' ordinata ci si puo' fermare al primo nickname di valore maggiore
														//e concludere che il nickname cercato non e' nella lista
			return;	
		}
		q=s;
		s=s->next;
	}

	if(s==NULL){
		printf("Nessun utente con questo nome\n");
		return;
	}	
	
	if(s->user.seduto!=0){
		printf("Non puoi eliminare un utente seduto al tavolo\n");
		return;
	}
	
	if(s==*testa){
		*testa=(*testa)->next; 
	}
	else{
		q->next=s->next;
	}
	
	
	
	free(s);
	
	printf("Utente eliminato\n");
	
	return;

	
	
}

void cancellaNick(l_nickname** testa, char nick[]){
	l_nickname* q=*testa,*s=*testa;
	while((s!=NULL)&&(strcmp(s->nick,nick)!=0)){
		
		if(strcmp(s->nick,nick)>0){
			return;
		}
			
		
		q=s;
		s=s->next;
	}

	if(s==*testa){
		*testa=(*testa)->next; 
	}
	else{
		q->next=s->next;
	}
	free(s);
	
	
	
	
	return;

	
	
}


void svuotaNick(l_nickname** testa, l_utenti* testa_u){
	l_nickname* p=*testa;
	l_utenti *q;
	
	
	
	while((*testa!=NULL)){
		p=*testa;
		q=testa_u;
		while(q!=NULL){		//ricerca nella lista utenti gli eventuali utenti seduti al tavolo e li fa alzare
			
			if(strcmp(q->user.nickname,p->nick)==0){
				
				q->user.seduto=0;			
			}
			q=q->next;
		}
		
		
		*testa=p->next;
		free(p);
	}
	return;
	
	
}

void svuotaTavoli(l_tavoli** testa,l_utenti* testa_u){
	l_tavoli* p=*testa;
	
	
	while((*testa!=NULL)){
		p=*testa;
		*testa=p->next;
		svuotaNick(&(p->t.testa),testa_u);	//per evitare memory leak bisogna svuotare anche la relativa lista di nickname
		free(p);
	}
	return;
	
	
}

void cancellaTavolo(l_giochi** testa, l_utenti* testa_u ,int num){
	l_tavoli* q=NULL,*s=s,*m;
	l_giochi* p=*testa;
	
	while(p!=NULL){
		s=p->gioco.testa;
		q=s;
		while((s!=NULL)&&(s->t.num!=num)){
			if(s->t.num>num)
				break;		//se si arriva a un tavolo di numero maggiore di quello cercato
							//si e' certi che questo tavolo non e' presente
			q=s;
			s=s->next;
		}
		if(s==NULL){
			p=p->next;;
		}
		else{
			if(s==p->gioco.testa){
			p->gioco.testa=p->gioco.testa->next; 
			}
			else{
				q->next=s->next;
			}
			svuotaNick(&(s->t.testa),testa_u);
			printf("Eliminazione avvenuta con successo\n");
			free(s);
			return;
		}
	}
	

	printf("Nessun tavolo con questo numero\n");
	return;
	
}

void cancellaGioco(l_giochi** testa, l_utenti* testa_u, char gioco[]){
	
	l_giochi* q=*testa,*s=*testa;
	while((s!=NULL)&&(strcmp(s->gioco.nome,gioco)!=0)){
		
		if(strcmp(s->gioco.nome,gioco)>0) 
			break;			//se si arriva a un gioco che in ordine alfabetico viene dopo il gioco cercato 
							//si e' certi che questo gioco non e' presente
		q=s;
		s=s->next;
	}

	if(s==NULL){
		printf("Nessun gioco con questo nome");
		return;
	}	

	if(s==*testa){
		*testa=(*testa)->next; 
	}
	else{
		q->next=s->next;
	}
	svuotaTavoli(&(s->gioco.testa),testa_u);	//per evitare memory leak bisogna prima svuotare la lista di tavoli
	free(s);
	
	printf("Operazione effettuata con successo\n");
	return;
	
	
	
}

void aggiornaSaldo(l_utenti* testa, char str[]){
	
	l_utenti* p=testa;
	float vincita;
	
	do{		//si evita il primo confronto tra p e NULL perche' si e' certi che nella lista e' presente un utente con il nickname cercato,
			//in quanto questa funzione puo' essere invocata solo dalla iniziaPartita
		if(strcmp(p->user.nickname,str)==0){	//ricerca nella lista di utenti il nickname indicato, in modo da aggiornarne i dati dopo avere giocato
			vincita=p->user.saldo;
			vincita=(float)(rand()-RAND_MAX/2)*vincita/(float)RAND_MAX;		//genera un numero casuale (positivo o negativo) il cui valore assoluto non puo' superare il saldo iniziale del giocatore
			if(vincita>0)
				printf("\nL'utente %s ha vinto %.2f$\n",str,vincita);
			else
				printf("\nL'utente %s ha perso %.2f$\n",str,-vincita);
			p->user.saldo+=vincita;
			printf("Saldo aggiornato: %.2f\n",p->user.saldo);
			//p->user.seduto=0; //si alza dal tavolo
			return;
		}
		p=p->next;
	}while(p!=NULL);
	
	//return;
}

void iniziaPartita(l_giochi* testa_g, l_utenti* testa_u, int numTavolo){	//viene passata anche la lista di utenti in quanto necessaria per la chiamata alla funzione aggiornaSaldo
	
	l_giochi* p=testa_g;
//	l_utenti* s;
	l_tavoli* q;
	l_nickname* r;
	int min;
	float vincita;	
	
	
	
	
	while(p!=NULL){		//scorre la lista di giochi
		min=p->gioco.giocatori_min;		//memorizza il minimo numero di giocatori necessari per quel gioco
		q=p->gioco.testa;
		while(q!=NULL){		//scorre la listadi tavoli
			if(q->t.num>numTavolo)
				break;		//interrompe la ricerca nella lista di questo nodo se il tavolo raggiunto ha un numero maggiore del tavolo cercato
			if((q->t.num==numTavolo)){
				if(q->t.persone<min){		//se il tavolo viene trovato ma non ci sono abbastanza persone sedute la partita non puo' avere inizio
					printf("Non ci sono abbastanza giocatori per avviare la partita\n");
					return;
				}
				else{		//se il tavolo ha invece abbastanza giocatori: 
					q->t.persone=0;  //il contatore di persone sedute al tavolo viene azzerato 
					r=q->t.testa;
					while(r!=NULL){		//si scorre la lista dei nickname dei giocatori seduti al tavolo
						aggiornaSaldo(testa_u,r->nick);		//si invoca la funzione per generare le vincite e aggiornare il saldo di ognuno
									
						r=r->next;					
					}
					svuotaNick(&(q->t.testa),testa_u);		//la lista dei nickname dei giocatori seduti al tavolo viene svuotata e adesso il tavolo e' vuoto a tutti gli effetti
					return;
				}
			}
			
			q=q->next;
		}
		
		p=p->next;
	}
	//se la funzione esce completamente dal ciclo vuol dire che non c'erano tavoli con il numero indicato
	printf("Nessun tavolo con questo numero\n");
	return;
}

void lasciaTavolo(l_giochi** testa,utente u){

	l_giochi* p=*testa;
	l_tavoli* s;
		
	
	while(p!=NULL){		//scorre la lista di giochi
		s=p->gioco.testa;
		
		while(s!=NULL){		//per ogni gioco scorre la lista dei tavoli
		
			if(s->t.num==u.seduto){		//quando trova il numero corretto elimina il nickname dell'utente dalla lista di nickname puntata dal tavolo e decrementa il contatore di persone al tavolo
				cancellaNick(&(s->t.testa),u.nickname);
				s->t.persone--;
				printf("Ti sei alzato dal tavolo\n");
				return;
			}
			
			
			s=s->next;
		}
		
		p=p->next;
		
	}
	
	
	
	//return;

	//questa funzione puo' essere chiamata solo dopo login di un utente gia' seduto, e' virtualmente impossibile che la ricerca abbia esito negativo	
}




int login(l_utenti *testa, utente u, l_giochi** testa_giochi, utente** u2){		
	
	int scelta;
	l_utenti* s=testa;

	while(s!=NULL){
		if(((strcmp(s->user.nickname,u.nickname))==0)&&((strcmp(s->user.password,u.password))==0)){		//scorre la lista fino a trovare una combinazione nickname-password 
																										//che combaci con quella fornita da u
			
			if(strcmp(s->user.nickname,u.nickname)>0)	//la lista giocatori e' ordinata secondo i nickname, quindi se si trova un nickname che in ordine
														//alfabetico viene dopo u.nickname, e' inutile continuare la ricerca
				break;    
			
			if(s->user.seduto!=0){		//se la combinazione viene trovata ma l'utente risulta seduto, puo' alzarsi
				do{
					printf("Sei gia' online e seduto ad un tavolo: voi alzarti?\n 0)Si'  1)No\n");
					scanf("%d",&scelta);
					if((scelta>1)||(scelta<0))
						printf("Scelta non valida\n");
					
				}while((scelta>1)||(scelta<0));
				if(scelta==0){
					lasciaTavolo(testa_giochi,s->user);
					s->user.seduto=0;
				}
				else{
					return 2;
				}
			}
			else{		//se l'utente viene trovato ma non e' seduto
			
				if(s->user.online!=true){		
					s->user.online=true;
					printf("Login effettuato correttamente\n");
				}
				else{		//l'utente potrebbe essere gia' online ma inattivo (ovvero subito dopo avere giocato)
					printf("Sessione ripresa\nBuona fortuna per la tua prossima partita\n");				
				}
			}
			*u2=&(s->user);	//viene salvato l'indirizzo che contiene le informazioni dell'utente che ha fatto login
			
			return (*u2)->admin;		//restituisce 0 o 1 in caso di successo
		}
		s=s->next;
	}

	printf("Combinazione errata\n");

	return 2;		//in caso di errore 
	
}
/*
void logout(l_utenti *testa,char str[21]){
	l_utenti *p=testa;
	
	while(p!=NULL){
		
		if(strcmp(p->user.nickname,str)==0){
			p->user.online=false;
			printf("Logout effettuato con successo\n");
			return;
		}
		p=p->next;
	}
	
}
*/
void gestioneClienti(l_utenti** lista_u, int scelta, utente u){
	
	char str[21];
	
	switch(scelta){
		
		case 1:		//visualizza utenti
			stampaUtenti(*lista_u);
			break;
		case 2:		//elimina utente
			printf("Inserisci nickname dell'utente da eliminare: ");
			scanf("%s",str);
			if(strcmp(str,u.nickname)!=0)		//controlla che l'admin abbia inserito in str un nickname che non sia il suo
				cancellaUtente(lista_u,str,u);
			else
				printf("Non puoi eliminarti da solo\n");
			break;
	}
}

void gestioneGiochi(l_giochi** lista_g, l_utenti** lista_u, int scelta){
	
	char str[21];
	tipo_gioco g;
	
	switch(scelta){
		case 1:		//visualizza giochi
			stampaGiochi(*lista_g);
			break;
			
		case 2:		//inserisci gioco
			printf("Inserisci nome del gioco da inserire: ");
			scanf("%s",g.nome);
			do{
				printf("Inserisci numero minimo di giocatori: ");	//controlla che il numero minimo di giocatori sia almeno 1 e che il numero massimo sia maggiore del minimo
				scanf("%d",&g.giocatori_min);
				if(g.giocatori_min<1)
					printf("Numero non valido\n");
				}while(g.giocatori_min<1);
			do{
				printf("Inserisci numero massimo di giocatori: ");
				scanf("%d",&g.giocatori_max);
				if(g.giocatori_max<g.giocatori_min)
					printf("Numero non valido\n");
				}while(g.giocatori_max<g.giocatori_min);
				
			g.testa=NULL;		//inizializzazione puntatore a lista tavoli
			inserisciOrdin_giochi(lista_g,g);
			
			break;
				
		case 3:		//eliminazione gioco
			printf("Inserisci nome del gioco da eliminare: ");
			scanf("%s",str);
			cancellaGioco(lista_g,*lista_u,str);
			break;
	}
}

void gestioneTavoli(l_giochi** lista_g, l_utenti** lista_u, int scelta){
	
	int num;
	char str[21];
	tavolo t;
	l_tavoli *p,**q;
	
	switch(scelta){
		case 1:		//visualizza i tavoli
			stampaTavoli(*lista_g);
			break;
			
		case 2:		//aggiungi tavolo
			printf("Inserisci nome del gioco a cui il tavolo e' dedicato: ");
			scanf("%s",str);
			printf("Inserisci il numero del tavolo: ");
			scanf("%d",&t.num);
			t.persone=0;		//il tavolo subito dopo l'inserimento deve risultare vuoto, quindi i campi persone e testa devono essere opportunamente inizializzati
			t.testa=NULL;
			if(tavoloInseribile(*lista_g,t.num,str)==true){		//verifica la disponibilita' del tavolo
			
				q=cercaLista_tavoli(*lista_g,str);		//se il tavolo e' disponibile si cerca la testa della lista che deve contenerlo
				
				inserisciOrdin_tavoli(q,t);			
			}
			
			else{
				printf("Dati inseriti errati\n");
			}
			
			
			break;
			
		case 3:		//eliminazione tavolo
			printf("Inserisci il numero del tavolo da eliminare: ");
			scanf("%d",&num);
			cancellaTavolo(lista_g,*lista_u,num);
			break;
			
		case 4:		//inizio partita
			printf("Inserisci il numero del tavolo che vuoi fare giocare: ");
			scanf("%d",&num);
			iniziaPartita(*lista_g,*lista_u,num);
			break;
	}
}

void sottoMenu(l_giochi** lista_g, l_utenti** lista_u, int scelta, utente u){
	
	int sottoScelta=0;
	
	switch(scelta){			//il sottoMenu, a seconda della scelta effettuata nel precedente menu' stampa le possibili
							//operazioni per la gestione desiderata dall'amministratore, richiede un ulteriore scelta,
							//e procede alla chiamata della funzione di gestione necessaria
		case 1:
			do{	
				printf("\n\nGestione clienti\n\n");
				printf("1) Stampa lista utenti\n");
				printf("2) Cancella un utente\n");
				printf("0) Torna indietro\n");
				printf("Scegli l'operazione desiderata: ");
				scanf("%d",&sottoScelta);
		
				if((sottoScelta>3)||(sottoScelta<0)){
					printf("Scelta non valida\n");
				}
				else
					if(sottoScelta!=0)
						gestioneClienti(lista_u,sottoScelta, u);
			
			}while(sottoScelta!=0);
			
			
			break;
			
		case 2:
			do{	
				printf("\n\nGestione giochi\n\n");
				printf("1) Stampa lista giochi\n");
				printf("2) Inserisci un gioco\n");
				printf("3) Cancella un gioco\n");
				printf("0) Torna indietro\n");
				printf("Scegli l'operazione desiderata: ");
				scanf("%d",&sottoScelta);
		
				if((sottoScelta>3)||(sottoScelta<0)){
					printf("Scelta non valida\n");
				}
				else
					if(sottoScelta!=0)
						gestioneGiochi(lista_g,lista_u,sottoScelta);
			
			}while(sottoScelta!=0);
			
			
			break;
			
			
		case 3:
			do{	
				printf("\n\nGestione tavoli\n\n");
				printf("1) Stampa lista tavoli\n");
				printf("2) Inserisci un tavolo\n");
				printf("3) Cancella un tavolo\n");
				printf("4) Dai il via ad una partita\n");
				printf("0) Torna indietro\n");
				printf("Scegli l'operazione desiderata: ");
				scanf("%d",&sottoScelta);
		
				if((sottoScelta>4)||(sottoScelta<0)){
					printf("Scelta non valida\n");
				}
				else
					if(sottoScelta!=0)
						gestioneTavoli(lista_g,lista_u,sottoScelta);
			
			}while(sottoScelta!=0);
			
			
			break;
		
	}
	
	return;
	
}


void menuAdmin(l_giochi** lista_g, l_utenti** lista_u, utente* u){
	
	
	char ch;
	int scelta=0;
	
	
	
	do{	
	
		printf("\n\nCiao, %s, cosa desideri fare?\n",u->nickname);
		printf("1) Gestisci clienti\n");
		printf("2) Gestisci giochi\n");
		printf("3) Gestisci tavoli\n");
		printf("0) Logout\n");
		printf("Scegli l'operazione desiderata: ");
		scanf("%d",&scelta);
		
		if((scelta>3)||(scelta<0)){
			printf("Scelta non valida\n");
		}
			
		
	
	sottoMenu(lista_g,lista_u,scelta,*u);		//a seconda della scelta effettuata si passano le informazioni necessarie a un ulteriore menu'
	}while(scelta!=0);
	
	u->online=false;	//nuovo logout
	//logout(*lista_u,u.nickname);
	
	return;
	
}

bool siediti(l_giochi** testa, int numTavolo, utente** u){		//restituisce 0 se l'utente riesce a sedersi, 1 se cio' non e' possibile
																
	l_giochi *p=*testa;
	l_tavoli *s;
	l_nickname *n;
	
	int max;
	
	while(p!=NULL){		//scorre la lista di giochi
	
		max=p->gioco.giocatori_max;		//memorizza il massimo numero consentito di giocatori per quel tavolo
		s=p->gioco.testa;			//acquisisce la testa della lista di tavoli per il gioco considerato
		
		while(s!=NULL){
			
			if(s->t.num==numTavolo){		//scorre la lista e si ferma solo se il tavolo indicato viene trovato
				if(s->t.persone<max){		//se il tavolo non e' pieno aggiunge l'utente, ovvero incrementa il contatore di persone al tavolo
											//e aggiunge il nickname dell'utente alla lista di nickname puntata dal tavolo
					(*u)->seduto=numTavolo;
					s->t.persone++;
					inserisciOrdin_nickname(&(s->t.testa),(*u)->nickname);
				
					return true;
				}
				else{
                    printf("Il tavolo e' pieno\n");
					return false;			//se il tavolo e' pieno si ferma
				}
				
						
			}
			if(s->t.num>numTavolo)
				break; 			//se si arriva a un numero maggiore e' inutile continuare; si esamina quindi la lista di tavoli del gioco successivo
			s=s->next;
		}
		p=p->next;
	}
	
	printf("Nessun tavolo con questo numero, oppure il tavolo desiderato e' pieno\n");
	
	return false;
}


void menuUtente(l_giochi** lista_g, utente* u){
	
	char ch,cod[21];
	int scelta=0,numTavolo;
	float ricarica;
	bool seduto=false;
	
	
	
	do{	
	
		printf("\n\nCiao, %s, cosa desideri fare?\n",u->nickname);
		printf("1) Ricarica saldo (attuale: %.2f $)\n",u->saldo);
		printf("2) Visualizza tavoli\n");
		printf("3) Siediti a un tavolo\n");
		printf("0) Logout\n");
		printf("Scegli l'operazione desiderata: ");
		scanf("%d",&scelta);
		
		if((scelta>3)||(scelta<0)){
			printf("Scelta non valida\n");
		}
		
		switch(scelta){
			
			case 1:		//ricarica saldo
				printf("Inserisci il codice della tua carta di credito: ");
				scanf("%s",cod);
				if(strcmp(cod,u->codice)!=0){
					printf("Codice incorretto!\n");
					break;
				}
				printf("Inserisci la somma che vuoi ricaricare: ");
				do{
					scanf("%f",&ricarica);
					if(ricarica<0)
						printf("Errore nell'inserimento\n");
				}while(ricarica<0);
				u->saldo+=ricarica;
				printf("Ricarica effettuata\n");
				break;
			case 2:		//visualizza tavoli
				stampaTavoli(*lista_g);
				break;
				
			case 3:		//siediti a un tavolo
				if(u->saldo>0){
					printf("Inserisci il numero del tavolo a cui vuoi unirti: ");
					scanf("%d",&numTavolo);
					seduto=siediti(lista_g,numTavolo,&u);
					if(seduto==true)
						printf("Ti sei seduto\n");
				}
				else{
					printf("Il tuo saldo non e' sufficiente per giocare\n");
				}
				
				break;
				
				
			case 0:		//logout
				u->online=false;
				break;
		}
			
		
	
	}while((scelta!=0)&&(seduto==false));
	
		//uscita dal ciclo solo se l'utente richiede il logout o si siede a un tavolo
	
	
	return;
	
}





void menu(l_giochi** lista_g, l_utenti** lista_u){  //menu' principale
	
	char ch;
	int scelta=0,scelta2=0,prossimoMenu=0,annoNascita=0;   
	utente u,*u2;    
    u2=NULL;
	
	do{	
		printf("\n\nBenvenuto\n\n");
		printf("1) Login\n");
		printf("2) Registrazione\n");
		printf("0) Esci\n\n");
		printf("Scegli l'operazione desiderata: ");
		scanf("%d",&scelta);
		
		switch(scelta){		
			case 1:		//login
				printf("Inserisci il tuo nickname: ");
				scanf("%s",&u.nickname);
				printf("Inserisci la tua password: ");
				scanf("%s",&u.password);
				prossimoMenu=login(*lista_u,u,lista_g,&u2);	//passaggio per valore di un utente per verificare la sua presenza nella lista e passaggio
															//per riferimento di un puntatore a un utente che permettera' la manipolazione delle informazioni
															//relative all'utente che ha fatto login da parte dei menu' successivi
				
				if(prossimoMenu==0){		//controllo sul valore restituito dal login per potere avviare il giusto menu'
					
					menuAdmin(lista_g,lista_u,u2);
					}
					
				if(prossimoMenu==1)
					menuUtente(lista_g,u2);  
					
				printf("\n");		
				break;
			
			case 2:		//registrazione
				printf("Inserisci il tuo nome: ");
				scanf("%s",&u.nome);
				printf("Inserisci il tuo cognome: ");
				scanf("%s",&u.cognome);
				printf("Inserisci il codice della tua carta di credito: ");
				scanf("%s",&u.codice);
				printf("Inserisci il tuo nickname: ");
				scanf("%s",&u.nickname);
				printf("Inserisci la tua password: ");
				scanf("%s",&u.password);
				
				do{
					printf("Inserisci il tuo anno di nascita: ");
					scanf("%d",&annoNascita);
					if(((annoNascita>2020)||(2020-annoNascita)>99))
						printf("Anno non valido\n");
				}while((annoNascita>2020)||(2020-annoNascita)>99);
				
				
				do{
					printf("Sei un admin?\n 0)Si'  1)No\n");
					scanf("%d",&scelta2);
					if((scelta2>1)||(scelta2<0))
						printf("Scelta non valida\n");
					
				}while((scelta2>1)||(scelta2<0));
				u.admin=scelta2;
				u.online=false;
				u.seduto=0;
				if((2020-annoNascita)>18){
                    u.saldo=0;
					inserisciOrdin_utenti(lista_u,u);
                }
				else
					printf("Non sei maggiorenne\n");
				break;
				
			case 0:		//uscita dal programma
				printf("A presto\n");
				break;
			default:
				printf("Scelta non valida\n");
				break;
				
		}
		
	}while(scelta!=0);
	
	
	return;
}



void salva(l_giochi* testa_g, l_utenti* testa_u){
	
	FILE* fp=NULL;
	FILE* ft=NULL;
	
	l_giochi* p=testa_g;
	l_utenti* q=testa_u;
	l_tavoli* s;
	int numTavoli;
	
	fp=fopen("lista_giochi.txt","w");
	ft=fopen("lista_tavoli.txt","w");
	
	if((fp==NULL)||(ft==NULL)){
		printf("Errore nell'apertura del file");
		return;
	}
	while(p!=NULL){		//si scorre la lista dei giochi
		numTavoli=0;	//si presuppone che il gioco corrente non abbia tavoli dedicati
		fprintf(fp,"%s %d %d ",p->gioco.nome,p->gioco.giocatori_min,p->gioco.giocatori_max);    //scrittura su file delle informazioni riguardanti il gioco
		s=p->gioco.testa;		//accesso alla testa della lista di tavoli dedicato al gioco
		if(s!=NULL){
			fprintf(ft,"%s\n",p->gioco.nome);
			
			do{
				fprintf(ft,"%d ",s->t.num);		//se la lista non e' vuota si scrive sul file dei tavoli, memorizzando in una riga il nome del gioco a cui essi sono dedicati
												//e nella successiva i numeri dei tavoli separati da uno spazio
												
				numTavoli++;			//si incrementa il numero di tavoli scoperti nella lista di tavoli relativa al gioco
				s=s->next;
			}while(s!=NULL);
			fprintf(ft,"\n");		
		}
		fprintf(fp,"%d\n",numTavoli);		//si salva sul file relativo ai giochi il numero di tavoli trovati
		p=p->next;
	}
	
	fclose(fp);
	fclose(ft);

	
	

	fp=NULL;
	
	fp=fopen("lista_utenti.txt","w");
	
	
	
	if(fp==NULL){
		printf("Errore nell'apertura del file");
		return;
	}
	while(q!=NULL){
		fprintf(fp,"%s %s %s %s %s %.2f %d %s %s\n",q->user.nome,q->user.cognome,q->user.nickname,q->user.password,q->user.codice,q->user.saldo,q->user.seduto,(q->user.admin==0)?"Admin":"Utente",(q->user.online==0)?"Online":"Offline");
		//si scrivono le informazioni sugli utenti; per una migliore leggibilita' , gli interi 0 e 1 che indicano se l'utente e' offline/online-admin/utente
		//non sono salvati direttamente su file: al loro posto viene salvata una stringa restituita dopo controllo dell'operatore ternario '?:'
		q=q->next;
	}
	fclose(fp);
	
	return;
	
	
}

void inizializza(l_giochi** lista_g,l_utenti** lista_u){
	utente u,*p;
	tipo_gioco g;
	tavolo t;
	char nomegioco[21],str1[10],str2[10];
	int i,numTavoli;
	
	l_utenti* stackUtenti=NULL;   //dichiara tre pile di appoggio
	l_giochi* stackGiochi=NULL;
	l_tavoli* stackTavoli=NULL;
	
	FILE *fu=NULL,*fg=NULL,*ft=NULL;
	
	ft=fopen("lista_tavoli.txt","r");
	fg=fopen("lista_giochi.txt","r");
	fu=fopen("lista_utenti.txt","r");
	
	if((fg==NULL)||(fu==NULL)||(ft==NULL)){
		printf("Errore nell'apertura dei file\n");
		return;
	}
	
	while((fscanf(fg,"%s %d %d %d\n",&g.nome,&g.giocatori_min,&g.giocatori_max,&numTavoli))!=EOF){
		g.testa=NULL;
		if(numTavoli>0){   //se nel file di riferimento e' registrato un numero di tavoli maggiore di 0 per quel gioco, si puo' accedere al file in cui sono registrati i tavoli e salvare la prima riga
							//di tavoli, che sara' necessariamente presente per quel gioco
			fscanf(ft,"%s\n",nomegioco);
			for(i=0;i<numTavoli;i++){  //si acquisiscono i numeri nella riga che saranno tanti quanti numTavoli
				fscanf(ft,"%d ",&t.num);
				t.persone=0;      //si inizializza il tavolo
				t.testa=NULL;
				inserisciTesta_tavoli(&stackTavoli,t);     //si inserisce in testa a una pila
				
			}
			fscanf(ft,"\n");
			while(stackTavoli!=NULL){			//si svuota la pila con delle pop quando tutti i tavoli relativi al gioco sono stati letti
			
				inserisciTesta_tavoli(&(g.testa),popTavoli(&stackTavoli));	//gli elementi estratti dalla pop sono inseriti in testa alla lista utilizzata dal programma
																			//questo scambio di elementi tra pila di appoggio e lista garantisce una rapida acquisizione dal file
																			//e un rapido salvataggio sulla lista utilizzata dal programma (si effettuano soltanto operazioni che coinvolgono
																			//la testa della lista e della pila)
																			
			}			
			
		}
		inserisciTesta_giochi(&stackGiochi,g); //quando tutte le informazioni sul gioco sono acquisite si inserisce nella pila
	}
	
	while(stackGiochi!=NULL){   //svuotamento pila e salvataggio in lista
		inserisciTesta_giochi(lista_g,popGiochi(&stackGiochi));  
	}
	
	fclose(fg);
	fclose(ft);
	
	
	while((fscanf(fu,"%s %s %s %s %s %f %d %s %s\n",&u.nome,&u.cognome,&u.nickname,&u.password,&u.codice,&u.saldo,&u.seduto,str1,str2))!=EOF){
	
		u.admin=(strcmp(str1,"Admin")==0)?0:1;
	
		u.online=(strcmp(str2,"Online")==0)?0:1;   //lettura informazioni utente e conversione da stringa a intero delle informazioni sullo stato dell'utente
		
		inserisciTesta_utenti(&stackUtenti,u);    
		
		
		if(u.seduto>0){      //per evitare ulteriori letture e scritture su file per quanto riguarda la lista di nickname di persone sedute a un determinato tavolo
							//si invoca la funzione "siediti", sfruttando il fatto che conosciamo a priori a che tavolo ogni utente e' seduto e che abbiamo inizializzato
							//a 0 il numero di persone presenti a ogni tavolo durante il salvataggio da file (anche se questo non era vuoto al momento della scrittura su file)
			p=&u;
			siediti(lista_g,u.seduto,&p);
		}
		
		
	}
	
	while(stackUtenti!=NULL){
		inserisciTesta_utenti(lista_u,popUtenti(&stackUtenti));
	}




	fclose(fu);
	
	
	return;
	
	
}

void start(){
	l_giochi* lista_g=NULL;
	l_utenti* lista_u=NULL;
		
	inizializza(&lista_g,&lista_u);
	menu(&lista_g,&lista_u);
	salva(lista_g, lista_u);
	
	return;
}






