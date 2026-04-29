#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "enterBattle.h"
#include "InventoryItem.h"

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

        //subtract one from the choice so that the user gets 1 based counting
        int nextIdx = node->getNextIndex(choice-1);
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


//this is the roommate that you will talk to at the beginning of the game
class roomMateNPC : public TalkingNPC {
public:
  roomMateNPC() : TalkingNPC("Roommate", 11) {

    dialogueTree[0] = new DialogueNode(
      "Hey bro, I got this new energy drink. Wanna try it?",
      "1. Sure\n2. Where did you get it?\n3. Can't, I'm busy",
      { 3, 1, 2 }
    );

    dialogueTree[1] = new DialogueNode(
      "I met a guy out by the woods. A grad student maybe. Said it helped him get his life together.",
      "1. Sounds exactly like what I need\n2. Super sus dude",
      { 3,4 }
    );

    dialogueTree[2] = new DialogueNode(
      "Then this is exactly what you need. It will help you get stuff done. You will see things you've never seen before.",
      "1. What does that mean?\n2. I need things to disappear, not appear",
      { 5, 6 }
    );

    dialogueTree[3] = new DialogueNode(
      "How much do you want?",
      "1. Lemme taste it\n2. All of it",
      { 8, 9 }
    );

    dialogueTree[4] = new DialogueNode(
      "Bro, since when have you passed on trying anything that claims to provide energy?",
      "1. But I haven't seen this promoted on TikTok\n2. True, what could possibly go wrong.",
      { 7,9 }
    );

    dialogueTree[5] = new DialogueNode(
      "Who cares? Maybe you see the answers appearing on your paper.",
      "1. Sounds like exactly what I need\n3. No, this is focus time",
      { 4, 8 }
    );

    dialogueTree[6] = new DialogueNode(
      "But this will help you",
      "1. My brain will help me\n2. Okay, let's try it.",
      { 10, 9 }
    );

    dialogueTree[7] = new DialogueNode(
      "That just means you're ahead of the game.",
      "1. You're right\n2. Not this time",
      { 8, 10 }
    );

    dialogueTree[8] = new DialogueNode(
      "Thats the spirit", 
      "Press Enter to return to exit conversation", {}
    );

    dialogueTree[9] = new DialogueNode(
      "One glass of productivity coming up.", 
      "Press Enter to return to exit conversation", {}
    );

    dialogueTree[10] = new DialogueNode(
      "Fine, I'll go find someone else",
      "Press Enter to return to exit conversation", {}
    );

  }
};

//this guy is a total jerk. He might be a bad guy in disguise. It would be cool if you could punch him in the face
class hostileGuyNPC : public TalkingNPC {
public:
  hostileGuyNPC() : TalkingNPC("Jerk", 10) {

    dialogueTree[0] = new DialogueNode(
      "Get outta my way!",
      "1. Calm down\n2. Man, you were in my way\n3. Who are you?",
      { 1,2,3 }
    );

    dialogueTree[1] = new DialogueNode(
      "Why should I?",
      "1. It's good for your mental health\n2. It's not a big deal",
      { 4,5 }
    );

    dialogueTree[2] = new DialogueNode(
      "You have a lot of nerve trying to tell me what to do.",
      "1. I'm on a very important mission. Goodbye\n2. I was just making a simple observation",
      { 7,8 }
    );

    dialogueTree[3] = new DialogueNode(
      "Someone very important.",
      "1. I don't believe that\n2. Sorry, Mr. VIP. I didn't mean to interrupt your day.",
      { 6,9 }
    );

    dialogueTree[4] = new DialogueNode(
      "Look, when I need a therapist, I'll let you know. But not today.", 
        "Press 0 to exit conversation", {}
    );

    dialogueTree[5] = new DialogueNode(
      "I'll decide what's a big deal and what's not. And you need to watch where you're going.", 
        "Press 0 to exit conversation", {}
    );

    dialogueTree[6] = new DialogueNode(
      "Get out of here.", 
        "Press 0 to exit conversation", {}
    );

    dialogueTree[7] = new DialogueNode(
      "Well, try to avoid having your 'important stuff' interfere with my life.", 
        "Press 0 to exit conversation", {}
    );

    dialogueTree[8] = new DialogueNode(
      "Watch your mouth. A punch in the face might improve those powers of observation.", 
        "Press 0 to exit conversation", {}
    );

    dialogueTree[9] = new DialogueNode(
      "If you kept your eyes open, it would be obvious. And you would be able to stay out of my way.", 
      "Press 0 to exit conversation", {}
    );

  }
  void printDialogue(int currentIndex, Player* player) {
      // bounds checking to make sure index/node exists
      if (currentIndex < 0 || currentIndex >= dialogueTree.size()) return;

      DialogueNode* node = dialogueTree[currentIndex];

      //prints the npc's name and the NPC response(or greeting if the convo just started), then displays player options
      cout << "\n" << name << ": " << node->getNPCTalk() << "\n";
      cout << node->getPlayerChoices() << "\n";

      int choice;
      cin >> choice;

      if (currentIndex == 5 || currentIndex == 8 || currentIndex == 9) {
          player->alanEncounter = 1;
          enterBattle(player);
          player->alanEncounter = 0;
      }

      //subtract one from the choice so that the user gets 1 based counting
      int nextIdx = node->getNextIndex(choice - 1);
      if (nextIdx != -1) {
          printDialogue(nextIdx, player);
      }
  }
};

class englishProfessorNPC : public TalkingNPC {
public:
  englishProfessorNPC() :TalkingNPC("English Professor", 3) {
    dialogueTree[0] = new DialogueNode(
      "Hey, I've seen you in Epic and the Person. Let's see if you've been paying attention. On which circle of hell is Ulysses?",
      "1. Sixth\n2. Seventh\n3. Eighth\n4. Ninth",
      { 1,1,2,1 }
    );

    dialogueTree[1] = new DialogueNode(
      "Hmmm. You might want to read more carefully.",
      "",
      {}
    );

    dialogueTree[2] = new DialogueNode(
      "Good work, I see you have been paying attention. Here's something you might enjoy",
      "",
      {}
    );
  }

  void printDialogue(int currentIndex, Player* player) {
      // bounds checking to make sure index/node exists
      if (currentIndex < 0 || currentIndex >= dialogueTree.size()) return;

      DialogueNode* node = dialogueTree[currentIndex];

      //prints the npc's name and the NPC response(or greeting if the convo just started), then displays player options
      cout << "\n" << name << ": " << node->getNPCTalk() << "\n";
      cout << node->getPlayerChoices() << "\n";

      int choice;
      cin >> choice;

      if (currentIndex == 2) {
        InventoryItem* book = new InventoryItem("Book of Poems", 100, 10);
        player->addToInventory(*book);
        cout << "The professor hands you a brand new book of poetry.";
      }

      //subtract one from the choice so that the user gets 1 based counting
      int nextIdx = node->getNextIndex(choice-1);
      if (nextIdx != -1) {
          printDialogue(nextIdx, player);
      }
  }


};
