#include "visualization/GraphVisualize.h"

GraphVisualize::GraphVisualize(Font font) {
    this->font = font;
    this->progressBar = ProgressBar(font);
    this->isCreateChosen = false;
    std::string infor = "";
    this->numComponent = 0;

    this->createButton = Button({11.5, 434.5, 110, 30}, "Create", -1, BLACK, 20, font);
    this->connectedComponentButton = Button({11.5, 488, 110, 30}, "Component", -1, BLACK, 20, font);
    this->mstKruskalButton = Button({11.5, 541.5, 110, 30}, "MST", -1, BLACK, 20, font);
    this->randomButton = Button({156.5, 511, 110, 30}, "Random", -1, BLACK, 20, font);
    this->loadFileButton = Button({156.5, 552 , 110, 30}, "LoadFile", -1, BLACK, 20, font);
    this->inputEdges = InputStr(151.5, 422, 120, 25, "Num edge", 20, this->font);
    this->inputNodes = InputStr(151.5, 466, 120, 25, "Num vertex", 20, this->font);
}

GraphVisualize::~GraphVisualize() {
    // Placeholder for destructor
    // graph has been deleted in Graph destructor
    // colorComponent has been deleted in Graph destructor 
}

std::vector<Color> GraphVisualize::generateRandomColors(int n) {
    std::vector<Color> colors;
    colors.reserve(n);

    for (int i = 0; i < n; ++i) {
        unsigned char r = GetRandomValue(0, 255);
        unsigned char g = GetRandomValue(0, 255);
        unsigned char b = GetRandomValue(0, 255);
        colors.push_back(Color{r, g, b, 255});
    }

    return colors;
}

void GraphVisualize::randomize() {
    std::string v = this->inputNodes.getText();
    std::string e = this->inputEdges.getText();
    if (v.empty() || e.empty() ) return;
    this->inputEdges.changePlaceHolder(e);
    this->inputNodes.changePlaceHolder(v);
    this->infor = TextFormat("Randomize graph with v = %s, e = %s", v.c_str(), e.c_str());
    this->graph.randomize(std::stoi(v), std::stoi(e), 100);
    this->progressBar.updateMaxStep(1);
    this->progressBar.updateCurrentStep(1);
}

int GraphVisualize::loadFile() {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                           { "Text Files (.txt .text)", "*.txt *.text",
                               "All Files", "*" },
                           pfd::opt::force_path);
    if (f.result().empty()) {
        return 0;
    }
       
    auto path = f.result().back();
    this->infor = TextFormat("Load graph from file %s", path.c_str());
    this->graph.initFromFile(path.c_str());
    this->progressBar.updateMaxStep(1);
    this->progressBar.updateCurrentStep(1);
    return 1;
}

void GraphVisualize::connectedComponent() {
    this->infor = TextFormat("Find connected Component");
    this->numComponent = this->graph.connectedComponent();
    this->colorComponent = generateRandomColors(this->numComponent);
    this->progressBar.updateMaxStep(1);
    this->progressBar.updateCurrentStep(1);
}

void GraphVisualize::mstKruskal() {
    this->infor = TextFormat("Find minimun spanning tree with Kruskal algorithm");
    this->graph.mstKruskal();
    this->progressBar.updateMaxStep(1);
    this->progressBar.updateCurrentStep(1);
}

int GraphVisualize::handle() {
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (this->createButton.IsHovered()) {
            this->graph.resetMark();
            this->isCreateChosen = true;
            this->numComponent = 0;
            this->colorComponent.clear();
        }
        
        if (this->connectedComponentButton.IsHovered()) {
            this->graph.resetMark();
            this->isCreateChosen = false;
            connectedComponent();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        if (this->mstKruskalButton.IsHovered()) {
            this->graph.resetMark();
            this->isCreateChosen = false;
            this->numComponent = 0;
            this->colorComponent.clear();
            mstKruskal();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    if (this->randomButton.handle()) {
        randomize();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 1;
    }
    if (this->loadFileButton.handle()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        //if(!loadFile()) return 5;
        loadFile();
        return 5;
    }

    this->graph.updatePositions();

    return 0;
}

void GraphVisualize::drawButton() {
    this->createButton.draw(50);
    this->connectedComponentButton.draw(50);
    this->mstKruskalButton.draw(50);

    if(this->isCreateChosen) {
        inputNodes.draw();
        inputNodes.handle();
        inputEdges.draw();
        inputEdges.handle();
        DrawLineEx({126, 501}, {297, 501}, 1.3, THEME.SEPERATOR);
        this->randomButton.draw(50);
        this->loadFileButton.draw(50);
    }
}

void GraphVisualize::drawGraph() {
    this->graph.drawGraph(this->font, this->colorComponent);
}

void GraphVisualize::draw() {
    drawSideBar(0, "", {}, this->infor, this->progressBar, this->font);
    drawButton();
    drawGraph();
}