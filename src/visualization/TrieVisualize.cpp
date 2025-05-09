#include "visualization/TrieVisualize.h"

TrieVisualize::TrieVisualize(Font font) {
    this->font = font;
    this->progressBar = ProgressBar(font);
    this->isCreateChosen = false;
    this->isInsertChosen = false;
    this->isDeleteChosen = false;
    this->isSearchChosen = false;
    this->stepIndex = 0;
    this->frame = 0;
    this->type = false;
    this->numFrameOfAnimation = FPS;

    this->createButton = Button({8, 415, 110, 30}, "Create", -1, BLACK, 20, font);
    this->randomButton = Button({156.5, 449.3, 110, 30}, "Random", -1, BLACK, 20, font);
    this->loadFileButton = Button({156.5, 520.6, 110, 30}, "Load File", -1, BLACK, 20, font);
    this->insertButton = Button({8, 458, 110, 30}, "Insert", -1, BLACK, 20, font);
    this->deleteButton = Button({8, 504, 110, 30}, "Delete", -1, BLACK, 20, font);
    this->inputNumber = InputStr(156.5, 449.3, 110, 30, "", 20, this->font);
    this->playButton = Button({173, 492, 70, 30}, "Play", -1, BLACK, 20, font);
    this->searchButton = Button({8, 545, 110, 30}, "Search", -1, BLACK, 20, font);
}

TrieVisualize::TrieVisualize() : TrieVisualize(FONT) {}

TrieVisualize::~TrieVisualize() {
    // Placeholder for destructor
    // tree has its own destructor
}

void TrieVisualize::updateStep(int index) {
    this->step = this->tree.getProcess()[index];
    this->frame = 0;
    this->stepIndex = index;
}

void TrieVisualize::insert() {
    this->tree.insert(this->inputNumber.getText());
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void TrieVisualize::deleteNode() {
    this->tree.deleteStr(this->inputNumber.getText());
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void TrieVisualize::search() {
    this->tree.search(this->inputNumber.getText());
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void TrieVisualize::createFromFile() {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                           { "Text Files (.txt .text)", "*.txt *.text",
                               "All Files", "*" },
                           pfd::opt::force_path);
    if (f.result().empty()) {
        return;
    }
       
    auto path = f.result().back();
    this->tree.createFromFile(path.c_str());
    this->numFrameOfAnimation = 10/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void TrieVisualize::createWithRandomizedData(int n, int length) {
    this->tree.createRandom(n, length);
    this->numFrameOfAnimation = 10/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

int TrieVisualize::handle() {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (this->createButton.IsHovered()) {
            this->isCreateChosen = true;
            this->isDeleteChosen = false;
            this->isInsertChosen = false;
            this->isSearchChosen = false;
        }
        if (this->deleteButton.IsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = true;
            this->isInsertChosen = false;
            this->isSearchChosen = false;
        }
        if (this->insertButton.IsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = false;
            this->isInsertChosen = true;
            this->isSearchChosen = false;
        }
        if (this->searchButton.IsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = false;
            this->isInsertChosen = false;
            this->isSearchChosen = true;
        }
    }

    if (this->playButton.handle()) {
        if (this->isInsertChosen) {
            insert();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 2;
        }
        if (this->isDeleteChosen) {
            deleteNode();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 3;
        }
        if (this->isSearchChosen) {
            search();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 4;
        }
    }

    if (this->randomButton.handle()) {
        createWithRandomizedData();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    if (this->loadFileButton.handle()) {
        createFromFile();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 5;
    }

    int flag = this->progressBar.handle();
    if ( flag != 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    switch (flag)
    {
        case -2:
            if (this->progressBar.getMaxStep() == 0) break;
            this->progressBar.updateCurrentStep(-2);
            updateStep(0);
            break;

        case -1:
            if (this->progressBar.getMaxStep() == 0) break;
            this->progressBar.updateCurrentStep(-1);
            if (stepIndex == 0) return 0;
            updateStep(this->stepIndex - 1);
            break;

        case 1:
            if (this->progressBar.getMaxStep() == 0) break;
            if(stepIndex == this->tree.getProcess().size() - 1) break;
            this->progressBar.updateCurrentStep(1);
            updateStep(this->stepIndex + 1);
            break;

        case 2:
            if (this->progressBar.getMaxStep() == 0) break;
            updateStep((int)this->tree.getProcess().size() - 1);
            this->progressBar.updateCurrentStep(2);
            this->type = 2;
            break; 

        case 0:
            if (this->type == 2) {
                if (this->progressBar.getMaxStep() == 0) break;
                this->progressBar.updateCurrentStep(-2);
                updateStep(0);
                this->type = 1;
                break;
            }
            if (this->type == 1) {
                this->type = 0;
                break;
            }
            if (this->type == 0 && this->step.root->numOfChild) {
                this->type = 1;
                break;
            }

        case 3: case -3:
            this->numFrameOfAnimation = FPS/this->progressBar.getSpeed();

            break;

        default:
            break;
    }

    return 0;
}

void TrieVisualize::drawButtons() {
    this->createButton.draw(50);
    this->deleteButton.draw(50);
    this->insertButton.draw(50);
    this->searchButton.draw(50);

    if(this->isCreateChosen) {
        this->randomButton.draw(50);
        this->loadFileButton.draw(50);
    }

    if(this->isDeleteChosen || this->isInsertChosen || this->isSearchChosen) {
        this->inputNumber.draw();
        this->inputNumber.handle();
        this->playButton.draw();
    }
}

void TrieVisualize::drawNode(TrieNode *root, TrieNode* highlight, int frame, int numFrame, Font font, bool isNotification) {
    if (!root) return;
    
    Vector2 rootPos = Vector2Lerp(root->start, root->end, float(frame)/numFrame);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if(root->children[i]) {
            DrawLineEx(rootPos, Vector2Lerp(root->children[i]->start, root->children[i]->end, float(frame)/numFrame), 2, THEME.LINE);
        }
    }
    
    Color color = THEME.NODE;
    if(root->isEndStr) color = THEME.HIGHLIGHT_NODE_2;
    if(root == highlight && !isNotification) color = THEME.HIGHLIGHT_NODE_1;
    
    DrawCircle(rootPos.x, rootPos.y, NODE_RADIUS, color);
    Vector2 textSize = MeasureTextEx(font, TextFormat("%c", root->character), CODE_SIZE, 0);
    DrawTextPro(font, TextFormat("%c", root->character), {rootPos.x - textSize.x/2, rootPos.y - textSize.y/2}, {0.f, 0.f}, 0, CODE_SIZE, 0, BLACK);
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if(root->children[i]) {
            drawNode(root->children[i], highlight, frame, numFrame, font, isNotification);
        }
    }
}

void TrieVisualize::drawTree() {
    if (this->tree.empty()) {
        DrawCircle(779, 124, NODE_RADIUS, THEME.NODE);
        return;
    }
    if (this->tree.getProcess().empty()) return;
    drawNode(this->step.root, this->step.highlight, this->frame, this->numFrameOfAnimation, this->font, this->step.type == -1);
    if (this->type == 2 || this->type == 0) return;
    this->frame++;
    if(this->frame >= this->numFrameOfAnimation && !this->tree.getProcess().empty()) {
        if (stepIndex == this->tree.getProcess().size() - 1) {
            this->type = 2;
            return;
        }
        updateStep(this->stepIndex + 1);
        this->progressBar.updateCurrentStep(1);
    }

}

void TrieVisualize::draw() {
    drawSideBar(this->type, this->step.code, this->step.line, this->step.infor, this->progressBar, this->font);
    drawButtons();
    drawTree();
}

