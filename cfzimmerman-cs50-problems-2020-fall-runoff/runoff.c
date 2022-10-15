#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int candidatecheck = 0;
    
    // If the user inputs a name that matches a non-eliminated candidate, the voter's rank choices are updated. If the name input doesn't match any candidate's name, the candidatecheck variable stays at zero and an error message returns.
    for (int a = 0; a < candidate_count; a++)
    {
        if (strcmp(name, candidates[a].name) == 0)
        {
            preferences[voter][rank] = a;
            candidates[a].eliminated = false;
            candidatecheck ++;
        }
    }
    if (candidatecheck != 0)
    {
        return true;
    }
    
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int a = 0; a < voter_count; a++)
    {
        
        // candidates[preferences[a][b]].eliminated is understood as the boolean value of the candidate chosen by voter a in rank b.
        // If the top choice candidate for voter a isn't eliminated, that candidate gets a vote. If the top choice is eliminated, the algorithm checks the voter's other choices in order, recording a vote for the next-highest non-eliminated candidate.
        if (candidates[preferences[a][0]].eliminated == false)
        {
            candidates[preferences[a][0]].votes ++;
        }
        else if (candidates[preferences[a][0]].eliminated == true)
        {
            int shift = 0;
            
            while (candidates[preferences[a][shift]].eliminated == true)
            {
                shift ++;
            }
            
            candidates[preferences[a][shift]].votes ++;
        }
    }
    
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    
    // The ceil function rounds a float number up. Although it seems inefficient, I was only able to calculate the value of the towin integer by using two placeholder variables as I shifted between integer and float values.
    float vcount = (int)voter_count;
    float placeholder = ceil(vcount / 2);
    int towin = (int)placeholder;
    int b;
    for (b = 0; b < candidate_count; b++)
    {
        if (candidates[b].votes > towin)
        {
            printf("%s\n", candidates[b].name);
            return true;
        }
    }
    
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // The lowest score at the beginning of the function is the lowest score of the first non-eliminated candidate. Then, the function compares the votes of all non-eliminated candidates to determine the lowest score using the first candidate as a benchmark.
    int a = 0;
    while (candidates[a].eliminated == true)
    {
        a++;
    }
    int minimum = candidates[a].votes;
    
    for (int b = 0; b < candidate_count; b++)
    {
        if (candidates[b].eliminated == false)
        {
            if (candidates[b].votes < minimum)
            {
                minimum = candidates[b].votes;
            }
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    
    // If any of the non-eliminated candidates have non-equal scores, this function returns false.
    for (int a = 0; a < (candidate_count - 1); a++)
    {
        if (candidates[a + 1].eliminated == false)
        {
            if (candidates[a].votes != candidates[a + 1].votes)
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int a = 0; a < candidate_count; a++)
    {
        if (candidates[a].votes == min)
        {
            candidates[a].eliminated = true;
        }
    }
    return;
}
