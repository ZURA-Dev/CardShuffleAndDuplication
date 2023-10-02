#include <vector>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <random>
#include <chrono>
#include <thread>
using namespace std;

// this is a card shuffler checking whether the tale of "you can never get the same deck of cards twice"
// todo: shuffle cards
// check whether cards from previous shuffle matched
// Log how many shuffles, and how many matches, and on program end put a time lapse
// for memory management, for allDeckCheck only do it in portions of 50,000 then empty the vector

// for deck checks i need a way to track which decks matched, so i need to return maybe deck numbers?

class DataPair
{
public:
    vector<string> cards;
    int Number = 0;
    DataPair(const vector<string> &cards, int Number)
    {
        this->cards = cards;
        this->Number = Number;
    }
    void print()
    {
        for (int i = 0; i < cards.size(); i++)
        {
            cout << cards[i++] << " : " << Number << ", ";
        }
    }
};
class CardDeck
{
public:
    const int SIZE = 52;
    int shuffles = 0;
    int matches = 0;
    vector<string> cards = {"ClubA", "Club2", "Club3", "Club4", "Club5", "Club6", "Club7", "Club8", "Club9", "Club10", "ClubJack", "Club Queen", "ClubKing", "DiamondA", "Diamond2", "Diamond3", "Diamond4", "Diamond5", "Diamond6", "Diamond7", "Diamond8", "Diamond9", "Diamond10", "DiamondJack", "DiamondQueen", "DiamondKing", "HeartA", "Heart2", "Heart3", "Heart4", "Heart5", "Heart6", "Heart7", "Heart8", "Heart9", "Heart10", "HeartJack", "HeartQueen", "HeartKing", "SpadeA", "Spade2", "Spade3", "Spade4", "Spade5", "Spade6", "Spade7", "Spade8", "Spade9", "Spade10", "SpadeJack", "SpadeQueen", "SpadeKing"};
    vector<DataPair> previousShuffle;
    // just prints cards
    void printCards()
    {
        for (int i = 0; i < SIZE; i++)
        {
            cout << cards[i++] << ", ";
        }
    }
    // shuffles cards, stores previous card deck
    void cardShuffleAndStore()
    {
        previousShuffle.push_back(DataPair(cards, shuffles++));
        random_shuffle(cards.begin(), cards.end());
    }
    void fakePrevShuffle()
    {
        vector<string> &tempCards = cards;
        previousShuffle.push_back(DataPair(tempCards, shuffles++));
    }
    // this goes through previous deck, and current deck to see if it matched
    void previousDeckCheck()
    {

        if (previousShuffle.empty())
        {
            return;
        }

        const vector<string> &prevCards = previousShuffle[shuffles - 1].cards;

        if (cards.size() != prevCards.size())
        {
            return;
        }

        int deckmatches = 0;

        for (int i = 0; i < cards.size(); i++)
        {
            if (cards[i] == prevCards[i])
            {
                matches++;
            }
        }
    }
    // this goes through all previous decks, and compares to current deck... need memory management
    void allDeckCheck()
    {
        if (previousShuffle.empty())
        {
            return;
        }
        int cardmatches = 0;
        for (int i = 0; i < previousShuffle.size(); i++)
        {
            for (int j = 0; j < cards.size(); j++)
            {
                if (previousShuffle[i].cards[j] == cards[j])
                {
                    cardmatches++;
                }
            }
            if (cardmatches == cards.size())
            {
                matches++;
                cardmatches = 0;
            }
        }
    }
    // this will initiate the continous loop of card shuffling and comparing
    void game()
    {
        while (true)
        {
            // Move the cursor up two lines using ANSI escape codes
            cout << "\033c";
            int i = 0;
            cardShuffleAndStore();
            previousDeckCheck();
            allDeckCheck();
            cout << "Current Shuffle Count: " << shuffles - 1 << endl;
            cout << "Current Matches: " << matches << endl;
        }
    }
};
int main()
{
    CardDeck card;
    card.game();
    return 0;
}