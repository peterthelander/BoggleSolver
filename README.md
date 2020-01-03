# BoggleSolver
A simple project that solves a Boggle Board

I had previously been thinking of a design where it would traverse over the game board to generate possible words, then see if those words are present in the dictionary using a dictionary lookup.

But it turns out that what seems to be a much better way to do it is by reversing that approach, and instead just iterate through all the words in the dictionary, and for each one see if it can be found in the game board. The design is much simpler that way, and it seems to be quite efficient, giving the solution in less than a second.

Regarding Optimization ...

There are a variety of things that could be done. In theory you could have a large lookup table which gives the complete list of words for each possible game board. In practice thats not feasible because there are 26^16 = 4.36e22 different game boards, and each one maps to a list of words which looks to be roughly 500 bytes. It would give O(1) for the operation of finding the solution for a given game board - the only problem is it would take alot of memory, and a long time for the pre-generation!

Other simpler optimizations for the design as I've done it, would be to skip checking any words in the dictionary that start with letters that are not on the board at all. Since there are only 16 letters on the board that should save some time. When going in to check if a word is on the board, the design as it stands right now will iterate over each co-ordinate in x and y to check the letters. So that improvement could be done using these lines at the beginning of GameBoard::containsWord :

    if (m_board.find(word[0]) == string::npos)
        return;

Another possible optimization is to then subdivide the dictionary into 26 sections, based on the first letter of words. Then entire sections can be skipped based on the first letter not being present in the board at all.

Cheers,
Peter
