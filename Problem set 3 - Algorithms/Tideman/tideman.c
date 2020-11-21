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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
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
    // TODO
    pair_count = 0;
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((preferences[i][j] > 0) && (preferences[i][j] > preferences [j][i]))
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }
    
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    
    for (int n = 0; n < pair_count; n++)
    {
        int max = 0;
        int max_index;
        
        for (int m = n; m < pair_count; m++)
        {
            if (preferences[pairs[m].winner][pairs[m].loser] > max)
            {
                max = preferences[pairs[m].winner][pairs[m].loser];
                max_index = m;
            }
        }
        
        if (max_index != n)
        {
            pair temp_pair = pairs[n];
            pairs[n] = pairs[max_index];
            pairs[max_index] = temp_pair;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    int cycle(int stop, int winner);
    
    for (int n = 0; n < pair_count; n++)
    {
        locked[pairs[n].winner][pairs[n].loser] = true;
        
        if (cycle(pairs[n].winner, pairs[n].winner) == 1)
        {
            locked[pairs[n].winner][pairs[n].loser] = false;
        }
    }
    
    return;
}

int cycle(int stop, int winner)
{
    //return 0 if no cycle
    //return 1 if cycle 
   
    for (int x = 0; x < candidate_count; x++)
    {    
        if (locked[winner][x] == true)
        {
            if (x == stop)
            {
                return 1;
            }
            else
            {
                if (cycle(stop, x))
                {
                    return cycle(stop, x);
                }
            }
        }
    }
    return 0;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    
    for (int x = 0; x < candidate_count; x++)
    {
        bool winner = true;
        
        for (int y = 0; y < candidate_count; y++)
        {
            if (locked[y][x] == true)
            {
                winner = false;
            }
        }
        
        if (winner)
        {
            printf("%s\n", candidates[x]);
            return;
        }
    }
}

