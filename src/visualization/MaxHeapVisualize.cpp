#include "visualization/MaxHeapVisualize.h"

MaxHeapVisualize::MaxHeapVisualize(Font font) {
    this->font = font;
    this->progressBar = ProgressBar(font);
    this->isCreateChosen = false;
    this->isPushChosen = false;
    this->isDeleteChosen = false;
    this->stepIndex = 0;
    this->frame = 0;
    this->type = 0;
    this->numFrameOfAnimation = FPS;

    this->createButton = Button({8, 415, 110, 30}, "Create", -1, BLACK, 20, font);
    this->randomButton = Button({156.5, 449.3, 110, 30}, "Random", -1, BLACK, 20, font);                        
    this->loadFileButton = Button({156.5, 520.6, 110, 30}, "Load File", -1, BLACK, 20, font);                       
    this->pushButton = Button({8, 450, 110, 30}, "Push", -1, BLACK, 20, font);
    this->deleteButton = Button({8, 485, 110, 30}, "Delete", -1, BLACK, 20, font);
    this->inputNumber = InputStr(156.5, 449.3, 110, 30, "", 20, this->font);        
    this->playButton = Button({173, 492, 70, 30}, "Play", -1, BLACK, 20, font);                             
    this->topButton = Button({8, 555, 110, 30}, "Top", -1, BLACK, 20, font);
    this->sizeButton = Button({8, 520, 110, 30}, "Size", -1, BLACK, 20, font);
}

MaxHeapVisualize::MaxHeapVisualize() : MaxHeapVisualize(FONT) {}

MaxHeapVisualize::~MaxHeapVisualize() {
    // Placeholder for destructor
    // heap has been deleted in MaxHeap destructor
    // animation (origin in MaxHeap) has been deleted in MaxHeap destructor 
}

void MaxHeapVisualize::updateStep(int index) {
    this->animation = this->heap.getSteps()[index];
    this->frame = 0;
    this->stepIndex = index;
    updateAnimation();
}

int MaxHeapVisualize::updateAnimation() {
    if (this->type == 2 || this->type == 0) return 0;
    this->frame++;
    int flag = 0;
    if(this->frame >= this->numFrameOfAnimation && !this->heap.getSteps().empty()) {
        if (stepIndex == this->heap.getSteps().size() - 1) {
            this->type = 2;
            return 0;
        }
        updateStep(this->stepIndex + 1);
        this->progressBar.updateCurrentStep(1);
        flag = 1;
    }

    switch (this->animation.type)
    {
        case 1:{
            Vector2 pos1 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[0]].pos;
            Vector2 pos2 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[1]].pos;
            this->animation.nodes[this->animation.highlight[0]].pos = Vector2Lerp(pos1, pos2, float(this->frame)/this->numFrameOfAnimation);
            this->animation.nodes[this->animation.highlight[1]].pos = Vector2Lerp(pos2, pos1, float(this->frame)/this->numFrameOfAnimation);
            break;
        }

        case 2:{
            if(this->frame < this->numFrameOfAnimation/2){
                this->animation.nodes[this->animation.highlight[0]].fontSize = FloatLerp(CODE_SIZE, 0, 2*float(this->frame)/this->numFrameOfAnimation);
            } else {
                this->animation.nodes[this->animation.highlight[0]].fontSize = FloatLerp(0, CODE_SIZE, 1.f - 2*float(this->frame)/this->numFrameOfAnimation);
            }
            break;
        }

        case 3:{
            Vector2 pos1 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[1]].pos;
            Vector2 pos2 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[0]].pos;
            this->animation.nodes[this->animation.highlight[0]].pos = Vector2Lerp(pos1, pos2, float(this->frame)/this->numFrameOfAnimation);
            this->animation.nodes[this->animation.highlight[0]].fontSize = FloatLerp(0, CODE_SIZE, float(this->frame)/this->numFrameOfAnimation);
            break;
        }

        case 4:{
            Vector2 pos1 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[1]].pos;
            Vector2 pos2 = this->heap.getSteps()[this->stepIndex].nodes[this->animation.highlight[0]].pos;
            this->animation.nodes[this->animation.highlight[0]].pos = Vector2Lerp(pos2, pos1, float(this->frame)/this->numFrameOfAnimation);
            this->animation.nodes[this->animation.highlight[0]].fontSize = FloatLerp(CODE_SIZE, 0, float(this->frame)/this->numFrameOfAnimation);
            break;
        }

        default:
            break;
    }
    return flag;
}

void MaxHeapVisualize::createWithRandomizedData(int n, int range) {
    this->heap.createWithRandomizedData(n, range);
    this->numFrameOfAnimation = 3;
    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void MaxHeapVisualize::createFromFile() {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                           { "Text Files (.txt .text)", "*.txt *.text",
                               "All Files", "*" },
                           pfd::opt::force_path);
    if (f.result().empty()) {
        return;
    }
    auto path = f.result().back();
    this->heap.createFromFile(path.c_str());
    this->numFrameOfAnimation = 3;
    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void MaxHeapVisualize::push() {
    std::string text = this->inputNumber.getText();
    if (text.empty()) return;
    this->heap.push(std::stoi(text));
    this->numFrameOfAnimation = 60;

    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void MaxHeapVisualize::deleteNode() {
    std::string text = this->inputNumber.getText();
    if (text.empty()) return;
    this->heap.deleteElement(std::stoi(text));
    this->numFrameOfAnimation = 60;

    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void MaxHeapVisualize::getTop() {
    this->heap.top();
    this->numFrameOfAnimation = 60;
    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
    this->type = 1;
}

void MaxHeapVisualize::getSize() {
    this->heap.size();
    this->numFrameOfAnimation = 60;

    this->animation = this->heap.getSteps().front();
    this->progressBar.updateMaxStep((int)this->heap.getSteps().size() - 1);
    this->stepIndex = 0;
    this->frame = 0;
    this->progressBar.updateCurrentStep(0);
}

void MaxHeapVisualize::drawButtons() {
    this->createButton.draw(50);
    this->deleteButton.draw(50);
    this->pushButton.draw(50);
    this->topButton.draw(50);
    this->sizeButton.draw(50);
    if(this->isCreateChosen) {
        this->randomButton.draw();
        this->loadFileButton.draw();
    }
    if(this->isDeleteChosen || this->isPushChosen) {
        this->inputNumber.draw();
        this->inputNumber.handle();
        this->playButton.draw();
    }
}

void MaxHeapVisualize::draw() {
    drawSideBar(this->type, this->animation.code, this->animation.lines, this->animation.infor, this->progressBar, this->font);
    drawButtons();
    MaxHeapNamespace::drawHeap(this->animation, this->font);
}

int MaxHeapVisualize::handle() {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (this->createButton.IsHovered()) {
            this->isCreateChosen = true;
            this->isDeleteChosen = false;
            this->isPushChosen = false;
        }
        if (this->deleteButton.IsHovered()) {
            this->isCreateChosen = false;
            //this->inputNumber.resetText();
            this->isDeleteChosen = true;
            this->isPushChosen = false;
        }
        if (this->pushButton.IsHovered()) {
            this->isCreateChosen = false;
            this->isDeleteChosen = false;
            //this->inputNumber.resetText();
            this->isPushChosen = true;
        }
    }

    if (this->playButton.handle()) {
        if (this->isPushChosen) {
            push();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 2;
        }

        if (this->isDeleteChosen) {
            deleteNode();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return 3;
        }
    }

    if (this->topButton.handle()) {
        getTop();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 4;
    }

    if (this->sizeButton.handle()) {
        getSize();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 5;
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
            if(stepIndex == (int)this->heap.getSteps().size() - 1) break;
            this->progressBar.updateCurrentStep(1);
            updateStep(this->stepIndex + 1);
            break;

        case 2:
            if (this->progressBar.getMaxStep() == 0) break;
            updateStep((int)this->heap.getSteps().size() - 1);
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
            
            if (this->type == 0 && !this->animation.nodes.empty()) {
                this->type = 1;
                break;
            }
            
            break;

        case 3: case -3:
            this->numFrameOfAnimation = FPS/this->progressBar.getSpeed();

            break;

        default:
            break;
    }

    updateAnimation();

    return 0;
}
