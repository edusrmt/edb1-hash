struct Account {
    using AcctKey = int;

    const char *name;
    int id;    
    int bank;
    int agency;
    int account;
    float m_balance;

    AcctKey & getKey () {
        return account;
    }

    bool operator==(const Account &rhs) const {
        return id == rhs.id and bank == rhs.bank and agency == rhs.agency and account == rhs.account;
    }
};