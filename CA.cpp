#include <iostream>



/*
1. Let D= the number we wish to convert from decimal to binary.
2. Repeat until D=0
   a. If D is even, put "0" in the leftmost open column.
   a. Else if D is odd, put "1" in the leftmost open column, and subtract 1 from D.
   c. Divide D by 2.
*/
void convertRuleSetNumberToRuleSetArray(int ruleSetNumber, int ruleSet[]) {
    int arrPos = 7;
    while (ruleSetNumber != 0) {
        if (ruleSetNumber % 2 == 0) {
            ruleSet[arrPos] = 0;
        } else {
            ruleSet[arrPos] = 1;
        }

        arrPos--;
        ruleSetNumber /= 2;
    }
}

void displayGeneration(int gen[], int genLength) {
    for (int i = 0; i < genLength; i++) {
        std::cout << (gen[i] == 1 ? "#" : " ");
    }

    std::cout << std::endl;
}

int convertNeighborhoodToIndex(int left, int current, int right) {
    return left*4 + current*2 + right*1;
}

void computeNextGeneration(int currentGen[], int nextGen[], int genLength, int ruleSet[]) {  
    nextGen[0] = currentGen[0];
    nextGen[genLength - 1] = currentGen[genLength - 1];

    for (int i = 1; i < genLength - 1; i++) {
        //std::cout << convertNeighborhoodToIndex(currentGen[i - 1], currentGen[i], currentGen[i + 1]);
        nextGen[i] = ruleSet[convertNeighborhoodToIndex(currentGen[i - 1], currentGen[i], currentGen[i + 1])];
    }
}

int main() {
    std::cout << "Enter a number between 0 and 255 inclusive: ";
	int ruleSetNumber;
	std::cin >> ruleSetNumber;

	if (ruleSetNumber > 255 || ruleSetNumber < 0) {
		std::cout << "outside [0,255] range";
		return 0;
	}

    int ruleSet[8] = {0};
    convertRuleSetNumberToRuleSetArray(ruleSetNumber, ruleSet);

    // starting gen
    const int genLength = 64;
    int currentGen[genLength] = {0};
    currentGen[32] = 1;

    for (int i = 0; i < 50; i++) {
        displayGeneration(currentGen, genLength);
        int nextGen[genLength] = {0};
        computeNextGeneration(currentGen, nextGen, genLength, ruleSet);
        for (int j = 0; j < genLength; j++){
            currentGen[j] = nextGen[j];
        }
    }

	return 0;
}
