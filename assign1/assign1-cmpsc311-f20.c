////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmpsc311-f16-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMPSC311 at Penn State University.  See the related
//                   assignment page for details.
//
//   Author        : Michael Shi
//   Last Modified : ????
//

// Include Files
#include <stdio.h>
#include <cmpsc311_util.h>
#include <time.h>

// Defines
#define NUM_CARDS 52
#define MAX_CARDS 11
#define SPADE "\xE2\x99\xA0"
#define CLUB "\xE2\x99\xA3"
#define HEART "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"

// Functions
uint32_t getRandomValue(uint32_t min, uint32_t max); // Using strong randomness, generate random number

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_card
// Description  : print the card from the integer value
//
// Inputs       : card - the card to print
// Outputs      : 0 always

int print_card(int card)
{

  // CODE HERE
  char card_faces[] = "234567891JQKA";
  char *card_suits[] = {SPADE, CLUB, HEART, DIAMOND};
  int suit = card / 13, cardty = card % 13;
  if (cardty == 8)
  {
    printf("10%s", card_suits[suit]);
  }
  else
  {
    printf("%c%s", card_faces[cardty], card_suits[suit]);
  }
  return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : print_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always

int print_cards(int cards[], int num_cards)
{
  int i;
  for (i = 0; i < num_cards; i++)
  {
    int card = print_card(cards[i]);
    if (i % 13 == 12 && i != 0)
    {
      printf("%d \n", card);
    }
    else
    {
      printf("%d ", card);
    }
  }
  printf("\n\n");
  return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : shuffle_cards
// Description  : print a number of cards (no more than 13 on one line)
//
// Inputs       : cards - the array of cards to print
//                num_cards - the number of cards to print
// Outputs      : 0 always
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int shuffle_cards(int cards[], int num_cards)
{
  int i, j;
  for (i = num_cards - 1; i > 0; i--)
  {
    j = getRandomValue(0, i);
    swap(&cards[i], &cards[j]);
  }
  return (0);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : hand_value
// Description  : return the value of the hand
//
// Inputs       : cards - the array of cards in the hand
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int hand_value(int cards[], int num_cards)
{
  int sum = 0;
  int i;
  for (i = 0; i < num_cards; i++)
  {
    if (cards[i] % 13 < 9)
    {
      sum += cards[i] % 13 + 2;
    }
    else if (cards[i] % 13 < 12 && cards[i] >= 9)
    {
      sum += 10;
    }
    else
    {
      if (sum > 10)
      {
        sum += 1;
      }
      else
      {
        sum += 11;
      }
    }
  }
  return sum;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : sort_cards
// Description  : sort a collection of cards
//
// Inputs       : hand - the cards to sort
//                num_cards - the number of cards in the hand
// Outputs      : 0 always

int sort_cards(int hand[], int num_cards)
{
  int i, j;
  for (i = 0; i < num_cards - 1; i++)
  {
    for (j = 0; j < num_cards - 1 - i; j++)
    {
      if (hand[j] % 13 > hand[j + 1] % 13)
      {
        swap(&hand[j], &hand[j + 1]);
      }
      else if (hand[j] % 13 == hand[j + 1] % 13)
      {
        if (hand[j] > hand[j + 1])
        {
          swap(&hand[j], &hand[j + 1]);
        }
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

int dealer_play(int hand[], int num_cards)
{
  int hand_total = hand_value(hand, num_cards);
  if (hand_total < 17)
  {
    return (1);
  }
  else
  {
    return (0);
  }
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

int player_play(int hand[], int num_cards, int dealer_card)
{
  int hand_total = hand_value(hand, num_cards);
  if (dealer_card < 7)
  {
    if (hand_total < 12)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
  else
  {
    if (hand_total < 18)
    {
      return (1);
    }
    else
    {
      return (0);
    }
  }
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

float money_total = 100;
int play_hand(int deck[], int num_cards, float *player_money)
{
  shuffle_cards(deck, num_cards);
  int i;
  int player_hand[5];
  int dealer_hand[5];
  int player_hand_size = 2;
  int dealer_hand_size = 2;
  int *deck_ref;
  int deck_count = 4;
  deck_ref = &deck_count;
  player_money = &money_total;
  player_hand[0] = deck[0];
  dealer_hand[0] = deck[1];
  player_hand[1] = deck[2];
  dealer_hand[1] = deck[3];
  int player_hand_value = hand_value(player_hand, 2);
  int dealer_hand_value = hand_value(dealer_hand, 2);
  int x = player_play(player_hand, 2, dealer_hand[0]);
  int y = dealer_play(dealer_hand, 2);
  printf("---- New Hand ----\n\n");
  printf("Dealer Cards: ");
  printf("%d XX \n", print_card(dealer_hand[0]));
  printf("Player Cards: ");
  printf("%d \n", print_cards(player_hand, 2));
  if (player_hand_value == 21)
  {
    *(player_money) += 7.50;
    printf("Player has Blackjack!, wins $7.50\n");
    return (1);
  }
  while (x == 1)
  {
    for (i = 2; i < 5; i++)
    {
      int z = player_play(player_hand, player_hand_size, dealer_hand[0]);
      if (z == 0)
      {
        x = 0;
        break;
      }
      player_hand[i] = deck[*deck_ref];
      (*deck_ref)++;
      player_hand_size = i + 1;
      player_hand_value = hand_value(player_hand, player_hand_size);
      printf("Player hit (%d): ", player_hand_value);
      printf("%d \n", print_cards(player_hand, player_hand_size));
      
      if (player_hand_value > 21)
      {
        printf("Player BUSTS ... Dealer Wins!\n");
        *(player_money) -= 5;
        x = 0;
        return (0);
      }
    }
  }
  if (x == 0)
  {
    printf("Player stands (%d): ", player_hand_value);
    printf("%d \n", print_cards(player_hand, player_hand_size));
  }
  while (y == 1)
  {
    for (i = 2; i < 5; i++)
    {
      int z = dealer_play(dealer_hand, dealer_hand_size);
      if (z == 0)
      {
        y = 0;
        break;
      }
      dealer_hand[i] = deck[*deck_ref];
      (*deck_ref)++;
      dealer_hand_size = i + 1;
      dealer_hand_value = hand_value(dealer_hand, dealer_hand_size);
      printf("Dealer hit (%d): ", dealer_hand_value);
      printf("%d \n", print_cards(dealer_hand, dealer_hand_size));
      
      if (dealer_hand_value > 21)
      {
        printf("Dealer BUSTS ... Player Wins\n");
        *(player_money) += 5;
        y = 0;
        return (1);
      }
    }
  }
  if (y == 0)
  {
    printf("Dealer stands (%d): ", dealer_hand_value);
    printf("%d \n", print_cards(dealer_hand, dealer_hand_size));
  }
  if (player_hand_value > dealer_hand_value)
  {
    *(player_money) += 5;
    printf("Player Wins\n");
    return (1);
  }
  else
  {
    *(player_money) -= 5;
    printf("Dealer Wins\n");
    return (0);
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

int show_player_money_histogram(float money_rounds[], int last_round)
{
  int i, j;
  int max_money = 100;
  for (i = 0; i < last_round - 1; i++)
  {
    if (money_rounds[i] > max_money)
    {
      max_money = money_rounds[i];
    }
  }
  printf("\t\t\t\t\tPlayer Cash by Round\n");
  printf("      ---------------------------------------------------------------------------------------------------");
  for (i = 200; i > 0; i = i - 5)
  {
    for (j = 0; j <= 100; j++)
    {
      if (j == 0)
      {
        printf("\n %3d |", i);
      }
      else if (j == 100)
      {
        printf("|");
      }
      else if (money_rounds[j] >= i)
      {
        printf("X");
      }
      else
      {
        printf(".");
      }
    }
  }
  printf("\n      ---------------------------------------------------------------------------------------------------\n");
  printf("               1         2         3         4         5         6         7         8         9         10");
  printf("\n      1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
  return (0);
}
////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMPSC311 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main(int argc, char **argv)
{

  /* Local variables */
  int cmp311_deck[NUM_CARDS]; // This is the deck of cards
  int i;
  int win_count = 0;
  float money_round[99];
  int total_rounds;
  for (i = 0; i < 100; i++)
  {
    money_round[i] = 0;
  }

  /* Preamble information */
  printf("CMPSC311 - Assignment #1 - Fall 2020\n\n");
  srand(time(NULL));

  /* Step #1 - create the deck of cards */
  for (i = 0; i < NUM_CARDS; i++)
  {
    cmp311_deck[i] = i;
  }
  /* Step #2 - print the deck of cards */
  print_cards(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]));
  /* Step #4 - shuffle the deck */
  shuffle_cards(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]));
  /* Step #5 - print the shuffled deck of cards */
  print_cards(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]));
  /* Step #6 - sort the cards */
  sort_cards(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]));
  /* Step #7 - print the sorted deck of cards */
  print_cards(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]));
  /* Step #9 - deal the hands */
  for (i = 0; i < 100; i++)
  {
    money_round[i] = money_total;
    if (money_total > 5)
    {
      int hand_play = play_hand(cmp311_deck, sizeof(cmp311_deck) / sizeof(cmp311_deck[0]), &money_total);
      printf("After hand %d player has $%.2f left\n", i + 1, money_total);
      if (hand_play == 1)
      {
        win_count += 1;
      }
    }
    else
    {
      break;
    }
    total_rounds = i + 1;
  }
  printf("-------------\n");
  printf("Blackjack done - player won %d out of %d hands\n", win_count, total_rounds);
  /* Step 10 show historgrapm */
  show_player_money_histogram(money_round, sizeof(money_round) / sizeof(money_round[0]));
  /* Exit the program successfully */
  printf("\n\nCMPSC311 - Assignment #1 - Spring 2020 Complete.\n");
  return (0);
}
