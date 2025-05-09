#include "visualization/Tree234Visualize.h"

Tree234Visualize::Tree234Visualize(Font font) {
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

Tree234Visualize::Tree234Visualize() : Tree234Visualize(FONT) {}

Tree234Visualize::~Tree234Visualize() {
    // Placeholder for destructor
    // tree has its own destructor
}

void Tree234Visualize::updateStep(int index) {
    this->step = this->tree.getProcess()[index];
    this->frame = 0;
    this->stepIndex = index;
}

void Tree234Visualize::createFromFile() {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                           { "Text Files (.txt .text)", "*.txt *.text",
                               "All Files", "*" },
                           pfd::opt::force_path);
    if (f.result().empty()) {
        return ;
    }
       
    auto path = f.result().back();
    this->tree.createFromFile(path.c_str());
    if(this->tree.getProcess().empty()) return;
    this->numFrameOfAnimation = 10/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void Tree234Visualize::createWithRandomizedData(int n, int range) {
    this->tree.createRandom(n, range);
    if(this->tree.getProcess().empty()) return;
    this->numFrameOfAnimation = 10/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void Tree234Visualize::insert() {
    this->tree.insert(std::stoi(this->inputNumber.getText()));
    if(this->tree.getProcess().empty()) return;
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void Tree234Visualize::deleteNode() {
    this->tree.remove(std::stoi(this->inputNumber.getText()));
    if(this->tree.getProcess().empty()) return;
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void Tree234Visualize::search() {
    this->tree.search(std::stoi(this->inputNumber.getText()));
    if(this->tree.getProcess().empty()) return;
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->tree.getProcess().front();
    this->progressBar.updateMaxStep((int)this->tree.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}


int Tree234Visualize::handle() {
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
    if (flag != 10) {
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
            if (this->type == 0 && this->step.root) {
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

void Tree234Visualize::drawButtons() {
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

void Tree234Visualize::drawNode(Node234 *root, int frame, int numFrame, Font font, bool isNotification) {
    if (!root) return;

    if (root->keys.size() == 0) {
        Vector2 pos = Vector2Lerp(root->start, root->end, float(frame)/numFrame);
        DrawRectangleV(Vector2Add(pos, (Vector2){-15.f, 0.f}), {30.f, 30.f}, THEME.HIGHLIGHT_NODE_1);
        DrawLineEx(Vector2Add(pos, (Vector2){-0.f, 30.f}), Vector2Lerp(root->children[0]->start, root->children[0]->end, float(frame)/numFrame), 2, THEME.LINE);
    } else {
        for (int i = 0; i < root->children.size(); i++) {
            if(root->children[i]) {
                Vector2 linePos;
                if (i >= root->keys.size()) linePos = Vector2Add(Vector2Lerp(root->keys.back().start, root->keys.back().end, float(frame)/numFrame) , (Vector2){30.f, 30.f});
                else linePos = Vector2Add(Vector2Lerp(root->keys[i].start, root->keys[i].end, float(frame)/numFrame), (Vector2){0.f, 30.f});
                DrawLineEx(linePos, Vector2Lerp(root->children[i]->start, root->children[i]->end, float(frame)/numFrame), 2, THEME.LINE);
            }
        }
    }

    for (int i = 0; i < root->keys.size(); i++) {
        Color color = root->keys[i].highlight ? THEME.HIGHLIGHT_NODE_1 : THEME.NODE;
        Vector2 keyPos = Vector2Lerp(root->keys[i].start, root->keys[i].end, float(frame)/numFrame);
        DrawRectangleV(keyPos, {30.f, 30.f}, color);
        Vector2 textSize = MeasureTextEx(font, TextFormat("%d", root->keys[i].value), CODE_SIZE, 0);
        DrawTextPro(font, TextFormat("%d", root->keys[i].value), {keyPos.x + 15 - textSize.x/2, keyPos.y + 15 - textSize.y/2}, {0.f, 0.f}, 0, CODE_SIZE, 0, BLACK);
    }

    for (int i = 0; i < root->children.size(); i++) {
        if(root->children[i]) {
            drawNode(root->children[i], frame, numFrame, font, isNotification);
        }
    }
}

void Tree234Visualize::drawTree() {
    if (this->tree.getProcess().empty()) return;
    drawNode(this->step.root, this->frame, this->numFrameOfAnimation, this->font, this->step.type == -1);
    
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

void Tree234Visualize::draw() {
    drawSideBar(this->type, this->step.code, this->step.line, this->step.infor, this->progressBar, this->font);
    drawButtons();
    drawTree();
}
