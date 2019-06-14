/**
 * @brief Bank account struct
 * @author Eduardo Sarmento & Victor Vieira
 * 
 * A simple structs that represents a bank account.
 */
struct Account {
    using AcctKey = int; //<! Alias

    const char *name;   //<! The name information of the account.
    int id;             //<! The id of the account.
    int bank;           //<! The bank of the account.
    int agency;         //<! The agency of the account
    int account;        //<! The account number.
    float m_balance;    //<! The account balance value.

    /// Returns the account number.
    AcctKey & getKey () {
        return account;
    }

    /// Compares two accounts, if the id, bank, agency and account number are equal, return true, otherwise, returns false.
    bool operator==(const Account &rhs) const {
        return id == rhs.id and bank == rhs.bank and agency == rhs.agency and account == rhs.account;
    }
};