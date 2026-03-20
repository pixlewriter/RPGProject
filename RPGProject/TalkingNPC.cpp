#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DialogueNode {
private:

    string NPCDialogue;
    string playerChoices;
    vector<int> nextDialogues;

public:
    // Constructor to initialize the node
    DialogueNode(string NPCtalk, string choices, vector<int> next)
        : NPCDialogue(NPCtalk), playerChoices(choices), nextDialogues(next) {
    }

    // Getters, so the NPC can read data
    string getNPCTalk() const { return NPCDialogue; }
    string getPlayerChoices() const { return playerChoices; }

    // Returns the size to prevent out of bounds errors
    int getNumChoices() const { return nextDialogues.size(); }

    // Returns the index of the next node based on the player's pick
    int getNextIndex(int choice) const {
        if (choice >= 0 && choice < nextDialogues.size()) {
            return nextDialogues[choice];
        }
        return -1;
    }
};

class TalkingNPC {
protected:
    string name;
    vector<DialogueNode*> dialogueTree;

public:
    TalkingNPC(string npcName, int treeSize) : name(npcName) {
        dialogueTree.resize(treeSize, nullptr);
    }

    void printDialogue(int currentIndex) {
        // bounds checking to make sure index/node exists
        if (currentIndex < 0 || currentIndex >= dialogueTree.size()) return;

        DialogueNode* node = dialogueTree[currentIndex];

        //prints the npc's name and the NPC response(or greeting if the convo just started), then displays player options
        cout << "\n" << name << ": " << node->getNPCTalk() << "\n";
        cout << node->getPlayerChoices() << "\n";

        int choice;
        cin >> choice;

        int nextIdx = node->getNextIndex(choice);
        if (nextIdx != -1) {
            printDialogue(nextIdx);
        }
    }
//destructor
    virtual ~TalkingNPC() {
        for (auto node : dialogueTree) delete node;
    }
};


class ExampleNPC : public TalkingNPC {
public:
    ExampleNPC() : TalkingNPC("ExNPC", 3) { // 3 total nodes in this tree

        // Node 0: The Start
        dialogueTree[0] = new DialogueNode(
            "Hi how are you today?",
            "0: Fantastic.\n1: Could be better.\n2: Abysmal day.",
            { 1, 2, 2 } // Choices lead to index 1 or 2
        );

        // Node 1: Positive choice
        dialogueTree[1] = new DialogueNode(
            "Glad to hear it!",
            "", 
            // No choices = convo ends
            {}
        );

        // Node 2: Negative choice
        dialogueTree[2] = new DialogueNode(
            "How unfortunate :(",
            "",
            {}
        );
    }
};
/*int main() {
    // 1. Create the NPC object
    // This calls the ExampleNPC constructor, which fills the array.
    ExampleNPC* myEx = new ExampleNPC();

    // 2. Start the dialogue at the root (Index 0)
    // This will trigger the recursive printDialogue method we commented earlier.
    myEx->printDialogue(0);

    // 3. Clean up memory
    delete myEx;

    return 0;
}
*/