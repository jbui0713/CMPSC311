////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmpsc311-f16-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMPSC311 at Penn State University.  See the related
//                   assignment page for details.
//
//   Author        : Jefferson Bui
//   Last Modified : 9/16/20
//

// Include Files
#include <stdio.h>
#include <cmpsc311_util.h>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card( int card ) {

    // CODE HERE
    char card_faces[] = "234567891JQKA";
    char *card_suits[] = { SPADE, CLUB, HEART, DIAMOND };
    int suit = card / 13, cardty = card % 13;
    if ( cardty == 8 ) {
        printf( "10%s", card_suits[suit] );
    } else {
        printf( "%c%s", card_faces[cardty], card_suits[suit] );
    }

    // Return zero
    return( 0 );
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards(int cards[], int num_cards) {

	for (int i = 0; i < num_cards; i++){ // loop to print each card
		if (i%13 == 0){ //after 13 it prints to next line
			printf("\n");
		}
		printf("  ", print_card(cards[i]));
	}	
	printf("\n\n");
	return(0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int shuffle_cards( int cards[], int num_cards ) {
	uint32_t shuffle;
	int temp;
	while (num_cards){ //loop for shuffling
		shuffle = getRandomValue(0, num_cards--); // get value set between min, max
		temp = cards[num_cards]; //swap for shuffling
       	cards[num_cards] = cards[shuffle];
 		cards[shuffle] = temp;		
	}
	return(0);
}

 

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value( int cards[], int num_cards ) {
	int total_value = 0;
	for (int i = 0; i < num_cards; i++){
		int index_value = cards[i]%13; // gets the index value of cards
		if (index_value <= 8){ // cards index for 2-10, get plus 2 due to the true value being index + 2
			total_value += (index_value+2);
		} else if (index_value <= 11){ // values that K Q J are same
		       total_value += 10;
		} else {
			if(index_value = 12 || 25 || 38 || 51){
				if ((total_value + 11) > 21){ //check whether ace needs to be 1 or 11
					total_value += 1;
				} else {
	 				total_value += 11;
				}	
			}		
		}
	}		
	return(total_value);
 
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards( int hand[], int num_cards ) {
	int num1, num2, temp; //local variables created 
	for(num1=0; num1<NUM_CARDS-1; num1++){ 
		for(num2=num1+1; num2<NUM_CARDS; num2++){
			if(hand[num1]/13 > hand[num2]/13){ //sorts the card by suits first 
				temp=hand[num1];
				hand[num1] = hand[num2];
				hand[num2] = temp;
			}
			if(hand[num1]%13 > hand[num2]%13){ //sorts by the card's face value 
				temp=hand[num1];
				hand[num1] = hand[num2];
				hand[num2] = temp;
			}
		}
	}
        return (0);
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : dealer_play
// Description  : dealer decision to hit or stand (hit on anything less 
//                than 17)
//
// Inputs       : hand - cards dealer has
//                num_cards - the number of cards in player hand
// Outputs      : 0 = stand, 1 = hit

int dealer_play( int hand[], int num_cards ) {
	if (hand_value(hand, num_cards) < 17){ //rule of dealer need to hit if hand is less than 17
		return (1);
	}
	else	
		return (0);
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : player_play
// Description  : player decision to hit or stand
//
// Inputs       : hand - cards player has
//                num_cards - the number of cards in player hand
//                dealer_card - the dealers face up card
// Outputs      : 0 = stand, 1 = hit

int player_play( int hand[], int num_cards, int dealer_card ) {
	if(hand_value(hand, num_cards) < 16){ //player only call for hits if hand is less than 16
		return(1);
	}
	else
		return(0);
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : play_hand
// Description  : play a hand of black jack
//
// Inputs       : deck - the whole deck of cards
//                num_cards - the number of cards in the deck
//                player_money - pointer to player amount of money
// Outputs      : 1 if player wins, 0 if dealer wins

int play_hand( int deck[], int num_cards, float *player_money ) {
	int player_hand[MAX_CARDS]; //arrays set for the hands of player and dealer 
	int dealer_hand[MAX_CARDS];
	
	int deck_index;  	     //keeps track of size of hands and where in deck
	int player_index = 2;
	int dealer_index = 2;
	
	int player = hand_value(player_hand, player_index); //gets hand value for player and dealer
    	int dealer = hand_value(dealer_hand, dealer_index);
	
	
	shuffle_cards(deck, NUM_CARDS); //shuffles cards before dealing 
	
	player_hand[0] = deck[0]; //player gets first two cards
	player_hand[1] = deck[1]; //dealer gets next two
	dealer_hand[0] = deck[2];
	dealer_hand[1] = deck[3];
	
	deck_index = 4;
	
	printf("---- New hand -----\n\n");
	
    	printf("Dealer's Cards: ");	//only 1 of dealer card is revealed and 2 of player
    	print_card(dealer_hand[0]);
    	printf(" XX\n\n");
    	printf("Player's Cards: ");
    	printf(print_card(player_hand[0]));
    	printf(" ");
    	print_card(player_hand[1]);
    	printf("\n\n");
    	
    	
    	if(player == 21){   //if player hand value is 21, auto win
    		*player_money+=7.50;
    		printf("Player has Blackjack!, wins $7.50");
    		return(1);
    	}
    	while(player_play(player_hand, player_index, dealer_hand[0])){   
    		player_hand[player_index] = deck[deck_index];
    		player_index++;			//loop to check if player needs to hit, stand, or gets bust
    		deck_index++;
    		player_hand[player_index]+=deck[deck_index];
    		printf("Player hit (%d): ", hand_value(player_hand, player_index));
    		print_cards(player_hand, player_index);
    	}
    		
		player = hand_value(player_hand, player_index); //if hand value greater than 21 auto bust
    		if(player > 21){
    		*player_money-=5.0;
    		printf("Player BUSTS ... dealer wins!");
    		return(0);
    		}
    		
    		if(player > 16 && player < 21){ 	//desicion to stand or go back to hit
    			printf("Player stands (%d): ", hand_value(player_hand, player_index));
    			print_cards(player_hand, player_index);
    			printf("\n");
    		}
    	
    	
    	while(dealer_play(dealer_hand, dealer_index)){  //loop to check if dealer needs hit, stand, or gets bust
    		dealer_hand[dealer_index] = deck[deck_index];
    		dealer_index++;
    		deck_index++;
    		dealer_hand[dealer_index]+=deck[deck_index];
    		printf("Dealer hit (%d): ", hand_value(dealer_hand, dealer_index));
    		print_cards(dealer_hand, dealer_index);
    	}
    	
    		dealer = hand_value(dealer_hand, dealer_index); //if dealer hand greater than 21, bust
    		if(dealer > 21){
    		printf("Dealer BUSTS ... player wins!");
    		*player_money+=5.0;
    		return(1);
    		}
    		
    		if(dealer >= 17){ //if deal hand under 17, needs to hit 
    			printf("Dealer stands (%d): ", hand_value(dealer_hand, dealer_index));
    			print_cards(dealer_hand, dealer_index);
    			printf("\n");
    		}

    	
    		if (player>dealer){ 
    			printf("Player wins!!!");
    			*player_money+=5.0;
    			return(1);
    		}				//if no one has blackjac, hand values are compared to see who wins
    	
    		if(dealer>=player){
    			printf("Dealer wins!!!");
    			*player_money-=5.0;
    			return(0);
    		}
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : show_player_money_histogram
// Description  : Display a histogram of the player funds by hands
//
// Inputs       : money_rounds - the list of player money by hand number
//                last_round - the hand number where the game stopped
// Outputs      : 0 always

int show_player_money_histogram( float money_rounds[], int last_round ) {
	printf("\t\t\t\t\tPlayer Cash by Round\n");
	for (int i = 200; i >= 0; i-=5){ //loop to print the y axis 
		printf("%4d |",i);
		for (int j = 1; j < last_round; j++){ //loop for the x axis, tracking money
			if (i <= money_rounds[j]){
				printf("X");
			} else {
				printf(".");
			}
		}
		printf("|\n");
	}
	printf("      ");
			printf("----------------------------------------------------------------------------------------------------\n");
	printf("      ");
	printf("        1         2        3         4         5         6         7         8         9         10");
        printf("\n      ");
        printf("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");

}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMPSC311 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main( int argc, char **argv ) {

    /* Local variables */
    int cmp311_deck[NUM_CARDS];  // This is the deck of cards
    float bank_roll = 100.0;
    float *money_index = &bank_roll; //setting locals for money, hands, and rounds
    int hands_won = 0;
    float money_won[100];
    int hands_played = 1;
    int max_round = 99; 

    /* Preamble information */
    printf( "CMPSC311 - Assignment #1 - Fall 2020\n\n" );
    srand(time(NULL)) ;

    /* Step #1 - create the deck of cards */

    	for (int i=0; i<NUM_CARDS; i++){ //loop to create deck
    		cmp311_deck[i] = i;
    	}

    /* Step #2 - print the deck of cards */
	print_cards(cmp311_deck, NUM_CARDS);
	
    /* Step #4 - shuffle the deck */
    	shuffle_cards(cmp311_deck, NUM_CARDS);
    	
    /* Step #5 - print the shuffled deck of cards */
	print_cards(cmp311_deck, NUM_CARDS);
	
    /* Step #6 - sort the cards */
	sort_cards(cmp311_deck, NUM_CARDS);
	
    /* Step #7 - print the sorted deck of cards */
	print_cards(cmp311_deck, NUM_CARDS);
	
    /* Step #9 - deal the hands */
	while(hands_played < 100 && bank_roll >=5){ // game loop that runs for 100 rounds and as long as player has at least $5.
		if (play_hand(cmp311_deck, NUM_CARDS, money_index)){ //track times player wins
			hands_won++;
		}
		printf("\n\nAfter hand %d, player has %.2f$ left.\n",hands_played, bank_roll);
		money_won[hands_played] = bank_roll; //track money won by player
		hands_played++;
	}
	printf("\nBlackjack done. Player has won %d out of %d hands. (%.2f$)\n\n", hands_won, (hands_played), bank_roll);
	
    /* Step 10 show historgrapm */
	show_player_money_histogram(money_won, max_round);
    /* Exit the program successfully */
    printf( "\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n" );
    return( 0 );
}
