#pragma once
enum itemType
{
    none,
    parts,
    equipment,
    consumables
};

class item
{
protected:
    const itemType type;
    item* Next;
    char description[14][28];
    char name[20];
    char title[20];
    char pic[5][14];
    void fillTitle(const char* Title);
    int price;
    const int restriction;
    
public:
    item(const itemType type, const int Price,const int restr);
    item* getNext();
    int  getType()  const;
    int  getPrice() const;
    char getTitle(const int i) const;
    char getPic(int j, int i) const;
    char getName(const int i) const;
    const char* getTitle() const;
    char getDescript(int j, int i) const;
    void fillDescription(const char* Descript);
    void fillName(const char* Name);
    void clearDescript();
    void cleanTitle();
    void setNext(item* next);
    void showCount();
    void cleanCount();
    
    void craft();
    
    virtual void setCount(const int n);
    virtual void consume();
    
    virtual int  getProperty()    const;
    virtual int  getHp()          const;
    virtual int  getDef()         const;
    virtual int  getDmg()         const;
    virtual int  getPriority()    const;
    virtual int  getTurns()       const;
    virtual int  getCrit()        const;
    virtual int  getStun()        const;
    virtual int  getSplash()      const;
    virtual int  getPirs()        const;
    virtual int  getRestriction() const;
    virtual int  getCount()       const;
    virtual int  addCount(const int Count);
    virtual char * getPath();
};