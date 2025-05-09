#include "visualization/HashTableVisualize.h"

HashTableVisualize::HashTableVisualize(Font font) {
    this->table = HashTable(40);
    this->step = this->table.getProcess().front();
    this->font = font;
    this->progressBar = ProgressBar(font);
    this->isCreateChosen = false;
    this->isInsertChosen = false;
    this->isDeleteChosen = false;
    this->isSearchChosen = false;
    this->stepIndex = 0;
    this->frame = 0;
    this->numFrameOfAnimation = FPS;

    this->inputSize = InputStr(156.5, 422, 110, 30, "", 20, this->font);
    this->resizeButton = Button({156.5, 466, 110, 30}, "Resize", -1, BLACK, 20, font);
    this->createButton = Button({8, 415, 110, 30}, "Create", -1, BLACK, 20, font);
    this->randomButton = Button({156.5, 511, 110, 30}, "Random", -1, BLACK, 20, font);
    this->loadFileButton = Button({156.5, 552, 110, 30}, "Load File", -1, BLACK, 20, font);
    this->insertButton = Button({8, 458, 110, 30}, "Insert", -1, BLACK, 20, font);
    this->deleteButton = Button({8, 504, 110, 30}, "Delete", -1, BLACK, 20, font);
    this->inputNumber = InputStr(151.5, 422, 120, 25, "", 20, this->font);
    this->playButton = Button({173, 492, 70, 30}, "Play", -1, BLACK, 20, font);
    this->searchButton = Button({8, 545, 110, 30}, "Search", -1, BLACK, 20, font);
}

HashTableVisualize::HashTableVisualize() : HashTableVisualize(GetFontDefault()) {}

HashTableVisualize::~HashTableVisualize() {
    // table has been deleted in HashTable destructor
    // step (origin in HashTable) has been deleted in HashTable destructor 
    // Placeholder for destructor
}

void HashTableVisualize::updateStep(int index) {
    this->step = this->table.getProcess()[index];
    this->frame = 0;
    this->stepIndex = index;
}

void HashTableVisualize::resize() {
    this->table.resize(std::stoi(this->inputSize.getText()));

    this->numFrameOfAnimation = 5/this->progressBar.getSpeed();
    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void HashTableVisualize::insert() {
    this->table.insert(std::stoi(this->inputNumber.getText()));
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void HashTableVisualize::deleteNode() {
    this->table.deleteKey(std::stoi(this->inputNumber.getText()));
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void HashTableVisualize::search() {
    this->table.search(std::stoi(this->inputNumber.getText()));
    this->numFrameOfAnimation = 60/this->progressBar.getSpeed();

    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void HashTableVisualize::createFromFile() {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                           { "Text Files (.txt .text)", "*.txt *.text",
                               "All Files", "*" },
                           pfd::opt::force_path);
                           
    if (f.result().empty()) {
        return;
    }
       
    auto path = f.result().back();
    
    this->table.createFromFile(path.c_str());
    this->numFrameOfAnimation = 5/this->progressBar.getSpeed();

    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void HashTableVisualize::createWithRandomizedData(int n, int range) {
    this->table.createRandom(n, range);

    this->numFrameOfAnimation = 5/this->progressBar.getSpeed();

    this->step = this->table.getProcess().front();
    this->progressBar.updateMaxStep((int)this->table.getProcess().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

int HashTableVisualize::handle() {
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
        createWithRandomizedData(20, 100);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    if (this->loadFileButton.handle()) {
        createFromFile();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 5;
    }
    if(this->resizeButton.handle()) {
        resize();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return -10;
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
            if(stepIndex == this->table.getProcess().size() - 1) break;
            this->progressBar.updateCurrentStep(1);
            updateStep(this->stepIndex + 1);
            break;

        case 2:
            if (this->progressBar.getMaxStep() == 0) break;
            updateStep((int)this->table.getProcess().size() - 1);
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
            if (this->type == 0 && this->table.getProcess().size()) {
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

void HashTableVisualize::drawButtons() {
    this->createButton.draw(50);
    this->deleteButton.draw(50);
    this->insertButton.draw(50);
    this->searchButton.draw(50);

    if(this->isCreateChosen) {
        this->randomButton.draw(50);
        this->loadFileButton.draw(50);
        DrawLineEx({126, 501}, {297, 501}, 1.3, THEME.SEPERATOR);
        this->inputSize.draw();
        this->inputSize.handle();
        this->resizeButton.draw(50);
    }

    if(this->isDeleteChosen || this->isInsertChosen || this->isSearchChosen) {
        this->inputNumber.draw();
        this->inputNumber.handle();
        this->playButton.draw();
    }
}

void HashTableVisualize::drawTable() {
    if (this->table.getProcess().empty()) return;

    for (int i = 0; i < this->step.table.size(); i++) {
        int x = 350 + i % 10 * 80;
        int y = 150 + i / 10 * 80;
        DrawCircle(x, y, 15, this->step.highlightIndex == i ? THEME.HIGHLIGHT_NODE_1 : THEME.NODE);

        Vector2 size = MeasureTextEx(this->font, TextFormat("%d", i), CODE_SIZE - 2, 2);
        
        DrawTextEx(this->font, TextFormat("%d", i), {x - size.x/2, y + 25 - size.y/2}, CODE_SIZE - 2, 2, THEME.WEIGHT);

        if (this->step.table[i] >= 0) {
            size = MeasureTextEx(this->font, TextFormat("%d", this->step.table[i]), CODE_SIZE, 2);
            DrawTextEx(this->font, TextFormat("%d", this->step.table[i]), {x - size.x/2, y - size.y/2}, CODE_SIZE, 2, BLACK);
        }
    }

    if (this->type == 2 || this->type == 0) return;
    this->frame++;
    if(this->frame >= this->numFrameOfAnimation && !this->table.getProcess().empty()) {
        if (stepIndex == this->table.getProcess().size() - 1) {
            this->type = 2;
            return;
        }
        updateStep(this->stepIndex + 1);
        this->progressBar.updateCurrentStep(1);
    }
}

void HashTableVisualize::draw() {
    drawSideBar(this->type, this->step.code, this->step.line, this->step.infor, this->progressBar, this->font);
    drawButtons();
    drawTable();
}
