// include C libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// macros / global constants
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define	NAME 20
#define ROLLS 3
#define DICE 5
#define FALSE 0
#define TRUE 1
#define CATEGORY 13
#define COLS 2
#define FULLHOUSE 25
#define SMALLSTR 30
#define LARGESTR 40
#define YAHTZEE 50
#define BONUS 35
#define ISBONUS 63

struct Player
{
    int playerNum;
    char playerName[NAME];
    int scoreCard[CATEGORY][COLS];
};

// we will use the enums as indexes to the array that will store the scores
enum scores{one, two, three, four, five, six,
            threekind, fourkind, fullhouse, smstr,
            lgstr, yahtzee, chance};

// function prototypes
void welcomeScreen();
void playGame();
void displayEmptyCard();
void displayDice();
void displayRandomDice();
int rollDie();
void initDice(int dice[DICE]);
void rollDice(int dice[DICE], int keep[DICE]);
int selectDice(int dice[DICE], int keep[DICE]);
void displayRoll(int dice[DICE]);
void trimTrailing(char * str);
int isValid(char data[NAME]);
void initScorecard(int card[CATEGORY][COLS]);
int selectCategory();
void updateScores(int dice[DICE], int scoreCard[CATEGORY][COLS], int category);
void displayScoreCard(int scores[CATEGORY][COLS]);
void scoreUpper();
void scoreLowerKind();
void scoreFullHouse();
void scoreStraight();
void scoreYahtzee();
void scoreChance();
int compare();
int upperTotal();
int upperBonus();
int lowerTotal();
int grandTotal();

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();

    // seed the random function
    srand ((unsigned int) time (NULL));

    // call function playGame
    playGame();

    // program executed successfully
    return 0;
}

// welcomeScreen function displays the Yahtzee logo and rules of the game
void welcomeScreen ()
{
  printf ("\tY   Y    A    H   H TTTTT ZZZZZ EEEEE EEEEE\n");
  printf ("\t Y Y    A A   H   H   T      Z  E     E   \n");
  printf ("\t  Y    A   A  HHHHH   T     Z   EEE   EEE \n");
  printf ("\t  Y   A  A  A H   H   T    Z    E     E   \n");
  printf ("\t  Y   A     A H   H   T   ZZZZZ EEEEE EEEEE\n");
  printf ("\n");
  printf ("YAHTZEE GAME RULES\n\n");
    printf("\t 1. Five six-sided dice.\n");
    printf("\t 2. Players roll all five dice.\n");
    printf("\t 3. Players can roll selected dice three times per turn.\n");
    printf("\t 4. Player must score one of the 13 categories per turn.\n");
    printf("\t 5. Players alternate turns.\n");
    printf("\t 6. Game ends when all players score 13 categories.\n");
    printf("\t 7. Player with the highest score wins!\n");
}

void playGame()
{
    // arrays are inherently pointers to index 0 of the array
    // declare variable for each player as a struct
    struct Player playerOne;
    struct Player playerTwo;

//    char playerOne[NAME];
//    char playerTwo[NAME];

    int currentPlayer = ONE;
    int loop = ZERO;
    int dice[DICE];
    int keep[DICE];

    // prompt player one for their name and store in array playerOne
    printf("\nPlayer One, enter your name\n");
    scanf("%s", playerOne.playerName);
    playerOne.playerNum = ONE;

    // initialize the score card to all 0's
    initScorecard(playerOne.scoreCard);

    // prompt player two for their name and store in array playerTwo
    printf("Player Two, enter your name\n");
    scanf("%s", playerTwo.playerName);
    playerTwo.playerNum = TWO;

    // initialize the score card to all 0's
    initScorecard(playerTwo.scoreCard);

    // Let's play!
    printf("%s and %s let's play Yahtzee!\n", playerOne.playerName, playerTwo.playerName);

    // iterate two times
    while(loop < 26)
    {
        if(currentPlayer == playerOne.playerNum)
        {
            // prompt player it is their turn
            printf("%s it is your turn\n", playerOne.playerName);

            // call function displayEmptyCard
//            displayEmptyCard();
            displayScoreCard(playerOne.scoreCard);

            // call function initDice for arrays dice and keep
            initDice(dice);
            initDice(keep);

            // flush the standard in
            fflush(stdin);

            // call function rollDice
            rollDice(dice, keep);

            // prompt player to select a category
            int category = selectCategory();

            // update the player's score card
            updateScores(dice, playerOne.scoreCard, category);

            // display the player's score card
            displayScoreCard(playerOne.scoreCard);

            // switch players
            currentPlayer = playerTwo.playerNum;
        }
        else if(currentPlayer == playerTwo.playerNum)
        {
            // prompt player it is their turn
            printf("\n%s it is your turn\n", playerTwo.playerName);

            // call function displayEmptyCard
//            displayEmptyCard();
            displayScoreCard(playerTwo.scoreCard);

            // call function initDice for arrays dice and keep
            initDice(dice);
            initDice(keep);

            // call function rollDice
            rollDice(dice, keep);

            // prompt player to select a category
            int category = selectCategory();

            // update the player's score card
            updateScores(dice, playerTwo.scoreCard, category);

            // display the player's score card
            displayScoreCard(playerTwo.scoreCard);

            // switch players
            currentPlayer = playerOne.playerNum;
        }

        // increment the loop control variable
        loop++;
    }
}

// function displayEmptyCard displays a hardcoded version of a Yahtzee card
void displayEmptyCard()
{
    printf("+----------------------------------+\n");
    printf("| UPPER SECTION  |  LOWER SECTION  |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("| Aces   |       | 3 Kind  |       |\n");
    printf("|----------------------------------|\n");
    printf("| Twos   |       | 4 Kind  |       |\n");
    printf("|----------------------------------|\n");
    printf("| Threes |       | Full Hs |       |\n");
    printf("|----------------------------------|\n");
    printf("| Fours  |       | Sm Str  |       |\n");
    printf("|----------------------------------|\n");
    printf("| Fives  |       | Lg Str  |       |\n");
    printf("|----------------------------------|\n");
    printf("| Sixes  |       | Yahtzee |       |\n");
    printf("|----------------------------------|\n");
    printf("| Total  |       | Chance  |       |\n");
    printf("|----------------------------------|\n");
    printf("| Bonus  |       | Total   |       |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("|             Game Total   |       |\n");
    printf("+----------------------------------+\n");
}

// function displayDice displays hardcoded dice
void displayDice()
{
    printf("\n+---+ +---+ +---+ +---+ +---+\n");
    printf("| 6 | | 3 | | 5 | | 2 | | 4 |\n");
    printf("+---+ +---+ +---+ +---+ +---+\n");
 }

 // function displayRandomDice displays a randomly generated dice for three rolls
void displayRandomDice()
{
    // looping variable
    int roll;
    // dice variables
    int die1;
    int die2;
    int die3;
    int die4;
    int die5;

    // roll three times
    for(roll = ZERO; roll < ROLLS; roll++)
    {
        die1 = rollDie();
        die2 = rollDie();
        die3 = rollDie();
        die4 = rollDie();
        die5 = rollDie();

        printf("Roll %d\n", (roll + 1));

        printf("+-----+ +-----+ +-----+ +-----+ +-----+\n");
        printf("|  %d  | |  %d  | |  %d  | |  %d  | |  %d  |\n", die1, die2, die3, die4, die5);
        printf("+-----+ +-----+ +-----+ +-----+ +-----+\n");
    }
}

 // randomly rolls a die
int rollDie()
{
    // declare and initialize variable
    int dieValue = rand() % SIX + ONE;

    // return the value
    return dieValue;
}

void initDice(int dice[DICE])
{
    // loop through the five dice
    for(int die = 0; die < DICE; die++)
    {
        // set each die to FALSE
        dice[die] = FALSE;
    }
}

void rollDice(int dice[DICE], int keep[DICE])
{
    int roll = ZERO;

    // iterate through the three rolls
    while(roll < ROLLS)
    {
        printf("Roll %d\n", (roll + 1));

        // iterate through the five dice
        for(int die = 0; die < DICE; die++)
        {
            // only roll dice that have not been selected to keep
            if(keep[die] == FALSE)
            {
                dice[die] = rollDie();
            }
        }

        // display the current roll
        displayRoll(dice);

        // prompt the user to select the dice to keep
        // if the selected dice are not valid, player needs to be prompted again
        // without increasing the roll number
        if(selectDice(dice, keep) == FALSE)
        {
            printf("Selected dice invalid, try again\n");
        }
        else
        {
            roll++;
        }
    } // end while loop for three rolls
}

// prompts player to select the dice they want to keep from their roll
int selectDice(int dice[DICE], int keep[DICE])
{
    // store the player's input
    char input[NAME];
    char data[NAME];

    // variable for each token in string data
    char * value;

    // looping control variable to force user to select valid die
    int valid = FALSE;

    // prompt the user
    printf("\nSelect dice to keep, enter values 1 through 5 with spaces between numbers\n");

    // read the input
    fgets(input, NAME, stdin);

    // remove any trailing spaces
    trimTrailing(input);

    // check if the input is valid before parsing
    strcpy(data, input);
    valid = isValid(data);

    // if the input is not valid, return false
    if(!valid)
        return FALSE;

    // call initDice() for the keep array for each request
    // since users can change their mind for each roll
    initDice(keep);

    // parse the string into each value
    // priming read for first value
    value = strtok(input, " ");

    // loop to end of input
    while(value != NULL )
    {
        int number = atoi(value);

        switch(number)
        {
            case ONE:
                keep[ZERO] = TRUE;
                valid = TRUE;
                break;
            case TWO:
                keep[ONE] = TRUE;
                valid = TRUE;
                break;
            case THREE:
                keep[TWO] = TRUE;
                valid = TRUE;
                break;
            case FOUR:
                keep[THREE] = TRUE;
                valid = TRUE;
                break;
            case FIVE:
                keep[FOUR] = TRUE;
                valid = TRUE;
                break;
            default:
                break;
        }

        // read the next value
        value = strtok(NULL, " ");
    }

    return valid;
}

void displayRoll(int dice[DICE])
{
    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");
    printf("|       | |       | |       | |       | |       |\n");

    for(int die = 0; die < DICE; die++)
    {
        printf("|   %d   | ", dice[die]);
    }

    printf("\n");
    printf("|       | |       | |       | |       | |       |\n");
    printf("+-------+ +-------+ +-------+ +-------+ +-------+\n");
    printf("   (1)       (2)       (3)       (4)       (5)   \n");
}

int isValid(char data[NAME])
{
    int valid = FALSE;
    char * value;

    // parse the string into each value
    // priming read for first value
    value = strtok(data, " ");

    // loop to end of input
    while(value != NULL )
    {
        // convert the string data to integer
        int number = atoi(value);

        // if data is valid, set valid to TRUE
        if(number >= ONE && number <= FIVE)
        {
            valid = TRUE;
        }
        // else data is invalid, set valid to FALSE and break out of the loop
        else
        {
            valid = FALSE;
            break;
        }

        value = strtok(NULL, " ");
    }

    return valid;
}

void trimTrailing(char * str)
{
    // Set default index to invalid number
    int index = -1;

    // loop control variable
    int i = 0;

    // Find last index of non-white space character
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }

    // Mark next character to last non-white space character as NULL
    str[index + 1] = '\0';
}

void initScorecard(int card[CATEGORY][COLS])
{
    for(int row = 0; row < CATEGORY; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            // the first col should be set to values 0 - 12
            // use the looping variable as the value for the array element
            if(col == ZERO)
                card[row][col] = row;
            // else, set it to 0
            else
                card[row][col] = ZERO;
        }
    }
}

// prompt the player to select a category for scoring
int selectCategory()
{
    int select = ZERO;

    int valid = FALSE;

    while(!valid)
    {
        printf("\n\tSelect category for dice\n");
        printf("%d. Ones\n", one);
        printf("%d. Twos\n", two);
        printf("%d. Threes\n", three);
        printf("%d. Fours\n", four);
        printf("%d. Fives\n", five);
        printf("%d. Sixes\n", six);
        printf("%d. Three of a kind\n", threekind);
        printf("%d. Four of a kind\n", fourkind);
        printf("%d. Full house\n", fullhouse);
        printf("%d. Small straight\n", smstr);
        printf("%d. Large straight\n", lgstr);
        printf("%d. Yahtzee\n", yahtzee);
        printf("%d. Chance\n", chance);

        scanf("%d", &select);

        fflush(stdin);

        // validate the player's selected category
        if(select >= one && select <= chance)
        {
            valid = TRUE;
        }
        else
        {
            printf("\nInvalid category, try again\n");
            valid = FALSE;
        }
    }

    return select;
}

// update the player's score card based on the dice and category selecte
void updateScores(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    switch(category)
    {
        case one:
          scoreUpper(dice, scoreCard, category);
          break;

        case two:
          scoreUpper(dice, scoreCard, category);
          break;

        case three:
          scoreUpper(dice, scoreCard, category);
          break;

        case four:
          scoreUpper(dice, scoreCard, category);
          break;

        case five:
          scoreUpper(dice, scoreCard, category);
          break;

        case six:
          scoreUpper(dice, scoreCard, category);
          break;

        case threekind:
          scoreLowerKind(dice, scoreCard, category);
          break;

        case fourkind:
          scoreLowerKind(dice, scoreCard, category);
          break;

        case fullhouse:
          scoreFullHouse(dice, scoreCard, category);
          break;

        case smstr:
          scoreStraight(dice, scoreCard, category);
          break;

        case lgstr:
          scoreStraight(dice, scoreCard, category);
          break;

        case yahtzee:
          scoreYahtzee(dice, scoreCard, category);
          break;

        case chance:
          scoreChance(dice, scoreCard, category);
          break;

        default:
            printf("Invalid option, try again\n");
            break;
    }
}

// display the player's score card, the score is in the second column (i.e., ONE)
void displayScoreCard(int scores[CATEGORY][COLS])
{
    printf("+----------------------------------+\n");
    printf("| UPPER SECTION  |  LOWER SECTION  |\n");
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("| Aces   |   %d   | 3 Kind  |   %d   |\n", scores[one][ONE], scores[threekind][ONE]);
    printf("|----------------------------------|\n");
    printf("| Twos   |   %d   | 4 Kind  |   %d   |\n", scores[two][ONE], scores[fourkind][ONE]);
    printf("|----------------------------------|\n");
    printf("| Threes |   %d   | Full Hs |   %d   |\n", scores[three][ONE], scores[fullhouse][ONE]);
    printf("|----------------------------------|\n");
    printf("| Fours  |   %d   | Sm Str  |   %d   |\n", scores[four][ONE], scores[smstr][ONE]);
    printf("|----------------------------------|\n");
    printf("| Fives  |   %d   | Lg Str  |   %d   |\n", scores[five][ONE], scores[lgstr][ONE]);
    printf("|----------------------------------|\n");
    printf("| Sixes  |   %d   | Yahtzee |   %d   |\n", scores[six][ONE], scores[yahtzee][ONE]);
    printf("|----------------------------------|\n");
    printf("| Total  |   %d   | Chance  |   %d   |\n", upperTotal(scores), scores[chance][ONE]);
    printf("|----------------------------------|\n");
    printf("| Bonus  |   %d   | Total   |   %d   |\n", upperBonus(scores), lowerTotal(scores));
    printf("|----------------------------------|\n");
    printf("|----------------------------------|\n");
    printf("|             Game Total   |   %d   |\n",  grandTotal(scores));
    printf("+----------------------------------+\n");

}

// Function to compare two integers for qsort
int compare(const void *a, const void *b)
{
return (*(int *)a - *(int *)b);
}

// Calculate the total score for the upper section
void scoreUpper(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    int score = 0;

    for (int i = 0; i < DICE; i++){
        if(i == category + 1){
            score += dice[i];
        }
    }
    scoreCard[category][ONE] = score;
}

// Calculate the total score for the lower section
void scoreLowerKind(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    int counts[SIX] = {0};
    int score = 0;

    for (int i = 0; i < DICE; i++){
        counts[dice[i] - 1]++;
    }

    for (int i = 0; i < DICE; i++){
        score += dice[i];
    }

    for (int i = 0; i <= SIX; i++){
        if (category == threekind && counts[i] >= 3){
            scoreCard[category][ONE] = score;
        }
        else if (category == fourkind && counts[i] >= 4){
            scoreCard[category][ONE] = score;
        }
    }
}

// Calculate the score for the full house
void scoreFullHouse(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    int triple = 0;
    int pair = 0;
    int counts[SIX] = {0};

    for (int i = 0; i < DICE; i++){
        counts[dice[i] - 1]++;
    }

    for (int i = 0; i <= SIX; i++){
        if (counts[i] == 3){
            triple = TRUE;
        }
        if (counts[i] == 2){
            pair = TRUE;
        }
    }

    if (triple == TRUE && pair == TRUE){
        scoreCard[category][ONE] = FULLHOUSE;
    }
}

// Calculate the score for the straight
void scoreStraight(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    qsort(dice, DICE, sizeof(int), compare);
    int unique[DICE];
    int uniqueSize = 0;

    for (int i = 0; i < DICE; i++){
        if (uniqueSize == 0 || unique[uniqueSize - 1] != dice[i]){
            unique[uniqueSize++] = dice[i];
        }
    }

    if (category == smstr){
        for (int i = 0; i <= uniqueSize - 4; i++){
            if ((unique[i] == 1 && unique[i + 1] == 2 && unique[i + 2] == 3 && unique[i + 3] == 4) ||
                (unique[i] == 2 && unique[i + 1] == 3 && unique[i + 2] == 4 && unique[i + 3] == 5) ||
                (unique[i] == 3 && unique[i + 1] == 4 && unique[i + 2] == 5 && unique[i + 3] == 6)){
                scoreCard[category][ONE] = SMALLSTR;
                break;
            }
        }
    }

    if (category == lgstr){
        if ((unique[0] == 1 && unique[1] == 2 && unique[2] == 3 && unique[3] == 4 && unique[4] == 5) ||
            (unique[0] == 2 && unique[1] == 3 && unique[2] == 4 && unique[3] == 5 && unique[4] == 6)){
            scoreCard[category][ONE] = LARGESTR;
        }
    }
}

// Calculate the score for the yahtzee
void scoreYahtzee(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    int isYahtzee = TRUE;
    for (int i = 1; i < DICE; i++){
        if (dice[i] != dice[0]){
            isYahtzee = FALSE;
            break;
        }

        if (isYahtzee == TRUE){
            scoreCard[category][ONE] = YAHTZEE;
        }
    }
}

// Calculate the score for the chance
void scoreChance(int dice[DICE], int scoreCard[CATEGORY][COLS], int category){
    int score = 0;
    for (int i = 0; i < DICE; i++){
        score += dice[i];
    }

    scoreCard[category][ONE] = score;
}

// Calculate the total score for the upper section
int upperTotal(int scoreCard[CATEGORY][COLS]){
    int total = 0;
    for (int i = one; i <= six; i++){
        total += scoreCard[i][ONE];
    }
    return total;
}

// Calculate the total score for the lower section
int lowerTotal(int scoreCard[CATEGORY][COLS]){
    int total = 0;
    for (int i = threekind; i <= chance; i++){
            total += scoreCard[i][ONE];
        }
        return total;
    }

// Calculate the bonus score for the upper section
int upperBonus(int scoreCard[CATEGORY][COLS]){
    int total = 0;

    if (upperTotal(scoreCard) >= ISBONUS){
        total = BONUS;
    }

    return total;
}

// Calculate the grand total score
int grandTotal(int scoreCard[CATEGORY][COLS]){
    int total = upperTotal(scoreCard) + upperBonus(scoreCard) + lowerTotal(scoreCard) ;
    return total;
}