#include <iostream>
#include <map>
#include <string>
#include <exception>
#include <limits>


void dataInput(std::map<std::string, int>&);
bool inputEnd(std::map<std::string, int>&);
bool inputArticleControl( const std::string&, std::map<std::string, int>&);
bool inputNumCtrl(const int&);
void baseVisu(std::map<std::string, int>&, std::string&);
bool articleValidation(std::map<std::string, int>&, std::string&);
bool numValidation(std::map<std::string, int>&, std::string&, int&);
int  commandCtrl(std::string&);
void reducingNumInBase(std::map<std::string, int>&, std::string&, int&);
void inputArticleAtList(std::map<std::string, int>&, std::string&,std::string&);
void inNumAtliststd (std::map<std::string, int>&, std::string&, int&);



class Basket{
    std::map <std::string,int> productInBasket;

public:
    void add (std::map <std::string,int>& productInMarket, std::string& command){
        std::string inArticle;
        int inNum;
        bool inArticleCorrect=false;
        bool inArticleInBasket=false;

        inputArticleAtList(productInMarket,inArticle,command);
        inArticleCorrect= true;

        if(inArticleCorrect){
            inNumAtliststd(productInMarket,inArticle,inNum);
            inArticleInBasket=presenceArticleInBasket(inArticle);
            addingToBasket(inArticleInBasket,inArticle,inNum);
        }

        reducingNumInBase(productInMarket,inArticle,inNum);
    }
    void remove (std::string& command){
        std::string prodArticleBasket;
        int numProductInBasket;
        bool articleCorrect;

        if (!productInBasket.empty()){
            inputArticleAtList(productInBasket,prodArticleBasket,command);
            articleCorrect= true;

            if(articleCorrect){
                inNumAtliststd(productInBasket,prodArticleBasket,numProductInBasket);
                reducingNumInBase(productInBasket,prodArticleBasket,numProductInBasket);
            }
        }
        else{
            std::cout << "Product basket is empty!\n";
        }
    }

    void productInBasketVisu(){
        std::cout << "Now in basket: \n";
        for (auto it:productInBasket){
            std::cout << it.first << " " << it.second<<'\n';
        }
        std::cout << "\n";
    }

    bool presenceArticleInBasket(std::string & article){

        auto it =productInBasket.find(article);

        if(it->first ==article){
            std::cout << it->first<<" already in the basket\n";
            return true;
        }
        else {
            return false;
        }
    }

    void addingToBasket(bool& articleInBasket, std::string& article, int& num){
        if (articleInBasket){
            auto it = productInBasket.find(article);
                it->second+=num;
        }
        else{
            productInBasket.insert(std::make_pair(article,num));
        }
    }




};

int main() {

    std::map<std::string, int > productBase;
    bool addStatus= false;
    bool removeStatus=false;
    std::string command;

    while (inputEnd(productBase)){
        dataInput(productBase);
    }

    Basket* actBasket = new Basket;

    while (commandCtrl(command)!=4){

        std::cout << "To fill the basket, enter add.\n";
        std::cout << "To remove an item from the basket, enter remove\n";
        std::cout << "To exit enter end\n";
        std::cin >>command;
        if (commandCtrl(command)==0){
            std::cout << "Incorrect command, repeat!\n";
        }
        else if (commandCtrl(command)==1){
            do{
                try {
                    actBasket->add(productBase,command);
                    actBasket->productInBasketVisu();
                    addStatus= true;

                }
                catch(const std::exception& x) {
                    std::cerr << "Caught exception: "<<x.what()<<"\n";
                }

            } while (!addStatus);
        }
        else if(commandCtrl(command)==2){
            do {
                try{
                    actBasket->remove(command);
                    actBasket->productInBasketVisu();
                    removeStatus= true;
                }
                catch (const std::exception& y){
                    std::cerr << "Caught exception: "<<y.what()<<"\n";
                }
            } while (!removeStatus);
        }


    }

}


void dataInput(std::map<std::string, int>& base ){

    std::string article;
    int num ;

    do{
        std::cout << "Please enter the "<< base.size()+1<<" article in the base.\n";
        std::getline(std::cin, article);
    } while (!inputArticleControl(article,base));

    do {
        std::cout << " Please enter the num of  "<<article<<".\n ";
        std::cout << "To finish filling in the database, enter 9999\n";
        std::cin >> num;
    } while (!inputNumCtrl(num));

    std::pair<std::string, int> actPair =std::make_pair(article,num);
    base.insert(actPair);

}

bool inputArticleControl( const std::string& inputArticle, std::map<std::string, int>& base){

    for(int i =0;i< inputArticle.size();i++){
        if (inputArticle[i]<'0'||inputArticle[i]>'z'){
            std::cout << "Incorrect input, repeat!\n";
            return false;
        }
    }

    if (inputArticle.find(' ')!=std::string::npos){
        std::cout << "Incorrect input, repeat!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    for (auto it: base){
        if (it.first==inputArticle){
            std::cout << "This article is already in the database!\n";
            return false;
        }
    }
    return true;
}

bool inputNumCtrl(const int& inputNum){

    if (std::cin.good()){
        if (inputNum <=0 || inputNum >100000 ){
            std::cout << "Input num error, repeat\n";
            return false;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
    else{
        std::cout << "Input num error,repeat \n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

}

void baseVisu(std::map<std::string, int>& base, std::string& command){

    if (command=="add"){
        std::cout << " Now in market: \n";
    }
    else {
        std::cout << " Now in basket: \n";
    }

    for (auto it: base){
        std::cout <<  it.first<<" "<<it.second<<"\n";

    }
}

bool articleValidation(std::map<std::string, int>& prodBase , std::string& inArticle){
    for (auto it: prodBase)
        if (inArticle == it.first) {
            return true;
        }

    return false;
}

bool numValidation(std::map<std::string , int>& base , std::string& actArticle, int& inNum){
    for (auto it: base)
        if (actArticle == it.first) {
            if (inNum > it.second) {
                return false;
            }
        }

    return true;
}

bool inputEnd(std::map<std::string, int>& base){
    for (auto it :base ){
        if (it.first=="9999"||it.second==9999){
            base.erase(it.first);
            std::cout <<"Input completed, the database has been created!\n";
            return false;
        }
    }
    return true;
}


int commandCtrl(std::string& actCommand){
    if (actCommand=="add"){
        return 1;
    }
    else if (actCommand=="remove"){
        return 2;
    }
    else if(actCommand=="end"){
        return 4;
    }
    else{
        return 0;
    }
}

void reducingNumInBase(std::map<std::string, int>& base, std::string& article, int& num ){

      auto it=base.find(article);
      it->second-=num;
      if (it->second<0){
          it->second=0;
      }
}

void inputArticleAtList(std::map<std::string, int>& base , std::string& article, std::string& command){
    std::cout << "Please select product at list, input article \n";
    baseVisu(base,command);
    std::cin >>article;

    if (!articleValidation(base,article)){
        throw std::invalid_argument("Input error, invalid article!");
    }
}

void inNumAtliststd (std::map<std::string, int>& base, std::string& article, int& num){
    std::cout << "How many pieces "<<article<< " ? \n";
    std::cout << "Input num:  ";
    std::cin >> num;

    if (!numValidation(base,article,num)){
        throw std::invalid_argument("Input error,you have specified more than is available!\n ");
    }


}