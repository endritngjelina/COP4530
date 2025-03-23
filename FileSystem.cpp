//Endrit Ngjelina U43630372
#include <stdexcept>
#include <sstream>
#include <string>
#include <vector>

class FileSystemNode {
public:
    std::string name;
    bool isDirectory;
    FileSystemNode* parent;
    std::vector<FileSystemNode*> children;
    FileSystemNode(std::string name, bool isDir);
    ~FileSystemNode();
};

class FileSystem {
private:
    FileSystemNode* root;
    FileSystemNode* currentDirectory;
    FileSystemNode* findNode(FileSystemNode* startNode, const std::string& name);
    std::string displayTree(FileSystemNode* node, std::string indent);

public:
    FileSystem();
    ~FileSystem();
    void mkdir(const std::string& name);
    void touch(const std::string& name);
    std::string ls();
    void cd(const std::string& path);
    void rm(const std::string& name);
    std::string pwd();
    FileSystemNode* find(const std::string& name);
    std::string tree();
};

FileSystemNode::FileSystemNode(std::string name, bool isDir): name(name), isDirectory(isDir), parent(nullptr) {}

FileSystemNode::~FileSystemNode() {
    for (auto child : children) delete child;
}

FileSystem::FileSystem() {
    root = new FileSystemNode("/", true);
    currentDirectory = root;
}

FileSystem::~FileSystem() {
    delete root;
}

void FileSystem::mkdir(const std::string& name) {
    for (const auto& child : currentDirectory->children) if (child->name == name && child->isDirectory) throw std::runtime_error("Directory exists!");  //check if a directory with the same name exists in current directory

    FileSystemNode* new_directory = new FileSystemNode(name, true);
    new_directory->parent = currentDirectory;
    currentDirectory->children.push_back(new_directory);
}

void FileSystem::touch(const std::string& name) {
    for (const auto& child : currentDirectory->children) if (child->name == name && !child->isDirectory) throw std::runtime_error("File exists!");

    auto* new_file = new FileSystemNode(name, false);
    currentDirectory->children.push_back(new_file);
}

std::string FileSystem::ls() {
    std::stringstream string_segment;
    for (auto child : currentDirectory->children) {
        string_segment << child->name;
        
        if (child->isDirectory) string_segment << "/";
        string_segment << " ";
    }

    std::string string_result = string_segment.str();
    return string_result;
}

void FileSystem::cd(const std::string& path) {
    if (path == "/") {
        currentDirectory = root;    //move to the root directory
        return;
    }

    if (path == "..") {
        if (currentDirectory->parent != nullptr) currentDirectory = currentDirectory->parent;//move to parent directory if its not root
        return;
    }

    FileSystemNode* g_target = nullptr;   //find target directory in current directorys children
    for (auto child : currentDirectory->children) if (child->name == path && child->isDirectory) g_target = child;

    if (g_target) currentDirectory = g_target;  //change to found directory or throw error if not found
    else throw std::runtime_error("Directory not found!");
}

void FileSystem::rm(const std::string& name) {
    auto iterato = currentDirectory->children.begin();
    while (iterato != currentDirectory->children.end()) {
        if ((*iterato)->name == name) {
            currentDirectory->children.erase(iterato);
            return;
        }
        iterato++;
    }
    throw std::runtime_error("File or directory not found!");
}

std::string FileSystem::pwd() {
    std::string path;
    FileSystemNode* node = currentDirectory;

    while (node != nullptr && node->parent != nullptr) {    //traverse from current directory to the root, constructing path
        path = "/" + node->name + path;
        node = node->parent;
    }

    if (path.empty()) path = "/";   //add root slash if the root or if path is empty
    else path += "/";
    return path;
}

FileSystemNode* FileSystem::findNode(FileSystemNode* startNode, const std::string& name) {
    if (startNode->name == name) return startNode;
    for (auto child : startNode->children) FileSystemNode* found = findNode(child, name);
}

FileSystemNode* FileSystem::find(const std::string& name) {
    return findNode(root, name);
}

std::string FileSystem::displayTree(FileSystemNode* node, std::string indent) {
    std::stringstream ss;
    ss << indent << node->name << (node->isDirectory ? "/" : "") << "\n";
    if (node->isDirectory) for (auto child : node->children) ss << displayTree(child, indent + "  ");  
    return ss.str();
}

std::string FileSystem::tree() {
    return displayTree(root, "");
}