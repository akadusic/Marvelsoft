vector<any> AllNotestWithOneSymbol{
for(int i=0;i<parsedDocument.size();i++){
    BID bidHelp;
    ASK askHelp;
    vector<BID> helpBids;
    vector<ASK> helpAsks;
    vector<vector<BID>> allBidsForOneSymbol;
    vector<vector<ASK>> allAsksForOneSymbol;
    BOOK helpBook;
    TRADE helpTrade;
    vector<any> booksAndTrades;
    if(parsedDocument[i]["book"]["symbol"]==someText){
        for(int j=0;j<parsedDocument[i]["book"]["bid"].size();j++){
            postaviBidHelp;
            helpBids.push_back(bidHelp);
        }
        allBidsForOneSymbol.push_back(helpBids);
        helpBids.clear();
        for(int j=0;j<parsedDocument[i]["book"]["ask"].size();j++){
            postaviAskHelp;
            helpAsks.push_back(askHelp);
        }
        allAsksForOneSymbol.push_back(helpAsks);
        helpBook.bids = allBidsForOneSymbol;
        helpBook.asks = allAsksForOneSymbol;
        any book = helpBook;
        booksAndTrades.push_back(book);   
        helpAsks.clear();
    }
    if(parsedDocument[i]["trade"]["symbol"]==someText){
        for(int j=0;j<parsedDocument[i].size();j++){
            postaviHelpTrade;
        }
        any trade = helpTrade;
        booksAndTrades.push_back(book);
    }
    return booksAndTrades;
}
}
