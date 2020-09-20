#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int check_graph(int first, int next);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // check for name among candidates
        if (strcmp(name, candidates[i]) == 0)
        {
            // place candidate number in ranked order
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // iterate through all ranked candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // iterate through all ranked lower
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // iterate through all candidate combinations
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            // check who was more preferred
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // perform insertion sort
    pair x;
    int j;

    for (int i = 1; i < pair_count; i++)
    {
        x = pairs[i];
        j = i;

        while (j > 0 && preferences[x.winner][x.loser] >
               preferences[pairs[j - 1].winner][pairs[j - 1].loser])
        {
            pairs[j] = pairs[j - 1];
            j--;
        }

        pairs[j] = x;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // try to lock in every pair
    for (int i = 0; i < pair_count; i++)
    {
        // prevent cycle creation
        if (check_graph(pairs[i].winner, pairs[i].loser) == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool connected;
    bool clear;

    // check for all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        connected = false;
        clear = true;

        // check whether part of graph
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                connected = true;
            }
        }

        // check whether source of graph
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                clear = false;
            }
        }

        // print out winner
        if (connected && clear)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// function to recursively check for cycles
int check_graph(int first, int next)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[next][i])
        {
            if (i == first)
            {
                return 1;
            }
            else if (check_graph(first, i) == 1)
            {
                return 1;
            }
        }
    }

    return 0;
}