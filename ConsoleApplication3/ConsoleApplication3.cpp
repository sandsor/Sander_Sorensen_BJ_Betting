#include <iostream>
#include <ctime>

void shuffle(bool CardsDealt[]);
int getnextcard(bool Cardsdealt[]);
void PrintCard(int CardType);
int ScoreHand(int Hand[], const int CardCount);
void PrintHand(int Hand[], const int CardCount);
void PrintScoresandHands(int Hhand[], const int Hcards, int Phand[], const int Pcards);
int main()
{

    std::time_t qTime;  // \ 
    std::time(&qTime);  //  |>  these 3 lines makes it so that rand is truly random each time
    std::srand(qTime);  // / 


    bool CardsDealt[52];
    int Hcards = 0;
    int Hhand[12]; // you wont be able to draw 12 cards without busting
    int Pcards = 0;
    int Phand[12];
    int playerMoney = 100;
    int playerbet;
    while (true) {

        shuffle(CardsDealt);

        Phand[0] = getnextcard(CardsDealt);
        Hhand[0] = getnextcard(CardsDealt);
        Phand[1] = getnextcard(CardsDealt);
        Hhand[1] = getnextcard(CardsDealt);
        Pcards = 2;
        Hcards = 2;


        // this signals that a new game is begining

        std::cout << "--------------------------------------------------------" << std::endl;
        std::cout << "-----------------------New Hand-------------------------" << std::endl;
        std::cout << "--------------------------------------------------------" << std::endl;
        int Mchoise;
        char HitorStay;
        bool PlayerHit = true;
        int Pscore = ScoreHand(Phand, Pcards); // player score is based on the hand and the value of the cards
        std::cout << "This is your money ; " << playerMoney << "$" << std::endl;
        std::cout << "how much do you wanna bet ? : "; std::cin >> Mchoise;
        playerbet == Mchoise;
        playerMoney = playerMoney - Mchoise;
        do {
            // Here i display only one of the House's cards and both of the player's hand.
            std::cout << "House's Hand\n";
            std::cout << "** ";
            PrintCard(Hhand[1]);
            std::cout << "\n";
            std::cout << "Player's Hand: Score = " << ScoreHand(Phand, Pcards) << std::endl;
            PrintHand(Phand, Pcards);


            std::cout << "Wanna hit(h) or stay(s)? : ";
            std::cin >> HitorStay;
            if (HitorStay == 'h' || HitorStay == 'H') { // press h or s to play the game
                Phand[Pcards] = getnextcard(CardsDealt);
                ++Pcards;
            }
            else if (HitorStay == 's' || HitorStay == 'S') {
                PlayerHit = false;
            }
            else {
                std::cout << "Error: Try Again!\n"; // if no acceptable input arrives i send an error
            }
            std::cout << "\n";
            Pscore = ScoreHand(Phand, Pcards); // i make sure to update the hand info of player and house often,

        } while (PlayerHit && Pscore < 22);


        if (Pscore > 21) { // first we finf out if the player busts, before doing more
            std::cout << "---- House Wins! ----" << std::endl;
            PrintScoresandHands(Hhand, Hcards, Phand, Pcards);
        }
        else {
            int HouseScore = ScoreHand(Hhand, Hcards);
            while (HouseScore < 17) { // when player is done taking cards and isnt over 21, the house will draw cards until 17 or more
                Hhand[Hcards] = getnextcard(CardsDealt);
                ++Hcards;
                HouseScore = ScoreHand(Hhand, Hcards);
            }
            bool HouseBust = (HouseScore > 21);
            if (HouseBust) { // if the house busts the player wins
                std::cout << "---- The Player Wins! ----" << std::endl;
                PrintScoresandHands(Hhand, Hcards, Phand, Pcards);
                playerMoney = playerMoney + (Mchoise * 2);
            }
            else {
                if (Pscore == HouseScore) { // tie if both the house and player have the same score, also called push
                    std::cout << "---- Tie! ----" << std::endl;
                    PrintScoresandHands(Hhand, Hcards, Phand, Pcards);
                }
                else if (Pscore > HouseScore) { // if Player score is more than the house but not over 21 the player wins
                    std::cout << "---- The Player Wins! ----" << std::endl;
                    PrintScoresandHands(Hhand, Hcards, Phand, Pcards);
                    playerMoney = playerMoney + (Mchoise * 2);
                }
                else {
                    std::cout << "---- House Wins! ----" << std::endl;
                    PrintScoresandHands(Hhand, Hcards, Phand, Pcards);
                }
            }
        }
    }
}

void shuffle(bool CardsDealt[])
{
    for (int i = 0; i < 52; i++)
    {
        CardsDealt[i] = false;
    }
}

void PrintCard(int CardType) {
    // Prints card Ranks, so that i have kings and queens specified when drawn
    const int Rank = (CardType % 13);
    if (Rank == 0) {
        std::cout << 'A';
    }
    else if (Rank < 9) {
        std::cout << (Rank + 1);
    }
    else if (Rank == 9) {
        std::cout << 'T';
    }
    else if (Rank == 10) {
        std::cout << 'J';
    }
    else if (Rank == 11) {
        std::cout << 'Q';
    }
    else {
        std::cout << 'K';
    }
    // Prints The card types so that i get clover hearts etc...
    const int cType = (CardType / 13);
    if (cType == 0) {
        std::cout << 'C';
    }
    else if (cType == 1) {
        std::cout << 'D';
    }
    else if (cType == 2) {
        std::cout << 'H';
    }
    else {
        std::cout << 'S';
    }
}

void PrintHand(int Hand[], const int CardCount) { // gets value from main and calculates
    for (int i = 0; i < CardCount; i++) {
        const int NextCard = Hand[i];
        PrintCard(NextCard);
        std::cout << " ";
    }
    std::cout << std::endl;
}

int getnextcard(bool CardsDealt[])
{
    bool gettingcard = true;
    int newcard = -1;
    do {
        newcard = (rand() % 52);
        if (!CardsDealt[newcard]) {
            gettingcard = false;
        }
    } while (gettingcard);
    return newcard;
}

int ScoreHand(int Hand[], const int CardCount) // here i do the Ace calulations so that aces can be used as both 1 and 11
{
    int AceCount = 0;
    int Score = 0;
    for (int i = 0; i < CardCount; i++) {
        const int Nextcard = Hand[i];
        const int Rank = (Nextcard % 13);
        if (Rank == 0) {
            ++AceCount;
            ++Score;
        }
        else if (Rank < 9) {
            Score = Score + (Rank + 1);
        }
        else {
            Score = Score + 10;
        }
    }
    while (AceCount > 0 && Score < 12) {
        --AceCount;
        Score = Score + 10;
    }
    return Score;
}

void PrintScoresandHands(int Hhand[], const int Hcards, int Phand[], const int Pcards) { // this is just score board wich can get updated 
    std::cout << "House's Hand: Score = " << ScoreHand(Hhand, Hcards) << std::endl;
    PrintHand(Hhand, Hcards);
    std::cout << "Player's Hand: Score = " << ScoreHand(Phand, Pcards) << std::endl;
    PrintHand(Phand, Pcards);
    std::cout << std::endl;
}