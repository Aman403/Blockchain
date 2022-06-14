#include<bits/stdc++.h>

using namespace std;

//Transaction data

struct TransactionData{
	double amount;
	string senderKey;
    string receiverKey;
    time_t timestamp;
};

//block class

class Block{
	private:
		int index;
		size_t blockHash;
		size_t previousHash;
		size_t generateHash();
	
	public:
	 	//constructor
	 	Block(int idx,TransactionData d,size_t prevHash);
	 	
	 	///get Original Hash
	 	size_t getHash();
	 	
	 	//get previous Hash
	 	size_t getPreviousHash();
	 	
	 	//transaction data
	 	TransactionData data;
	 	
	 	//Validate Hash
	 	bool isHashValid();
};
//constructor with prames
Block::Block(int idx,TransactionData d,size_t prevHash)
{
	index=idx;
	data=d;
	previousHash=prevHash;
	blockHash=generateHash();
}


//private function
size_t Block::generateHash()
{
	hash<string> hash1;
	hash<size_t> hash2;
	hash<size_t> finalHash;
	string toHash=to_string(data.amount)+data.receiverKey+to_string(data.timestamp);
	
	return finalHash(hash1(toHash)+hash2(previousHash));
}

//public function

size_t Block::getHash()
{
	return blockHash;
}

size_t Block::getPreviousHash()
{
	return previousHash;
}

bool Block::isHashValid()
{
	return generateHash()==blockHash;
}

//blockchain Class

class Blockchain{
	private:
		Block createGenesisBlock();
		
	public:
		//public chain
		vector<Block> chain;
		
		//constructor
		
		Blockchain();
		
		//public functions
		void addBlock(TransactionData data);
		bool isChainValid();
		
		Block *getLatestBlock();
};

//Blockchain Construtor
Blockchain::Blockchain()
{
   Block genesis=createGenesisBlock();
   chain.push_back(genesis);	
} 

Block Blockchain::createGenesisBlock()
{
   time_t current;
   TransactionData d;
   d.amount =0;
   d.receiverKey="None";
   d.senderKey="None";
   d.timestamp=time(&current);
   
   hash<int> hash1;
   Block genesis(0,d,hash1(0));
   return genesis;
} 

//Bad only for demo

Block *Blockchain::getLatestBlock()
{
	return &chain.back();
	
}
void Blockchain::addBlock(TransactionData d)
{
	int index=(int)chain.size()-1;
	Block newBlock(index,d,getLatestBlock()->getHash());
	
}

bool Blockchain::isChainValid()
{
	vector<Block>::iterator it;
	int chainlen=(int)chain.size();
	
	for(it=chain.begin();it!=chain.end();++it)
	{
		Block currentBlock=*it;
		if(!currentBlock.isHashValid())
		{
			return false;
		}
		
		if(chainlen>1)
		{
			Block previousBlock=*(it-1);
			if(currentBlock.getPreviousHash()!=previousBlock.getHash())
			{
				//invalid 
				return false;
			}
		}
	}
	return true;
}

int main()
{
	//start Blocchain
	
	Blockchain AwesomeCoin;
	
	//Data for first added Block
	TransactionData data1;
	time_t data1Time;
	data1.amount=1.5;
	data1.receiverKey="joe";
	data1.senderKey="sally";
	data1.timestamp=time(&data1Time);
	
	AwesomeCoin.addBlock(data1);
	
	cout<<"Is chain Valid"<<endl<<AwesomeCoin.isChainValid()<<endl;
	TransactionData data2;
	time_t data2Time;
	data2.amount=1.5;
	data2.receiverKey="joe";
	data2.senderKey="sally";
	data2.timestamp=time(&data2Time);
	
	AwesomeCoin.addBlock(data2);
	cout<<"Is chain Valid"<<endl<<AwesomeCoin.isChainValid()<<endl;
	
	
	Block *hackBlock=AwesomeCoin.getLatestBlock();
	hackBlock->data.amount=1000;
	hackBlock->data.receiverKey="jon form alleu";
    cout<<"now chain is valid"<<endl<<AwesomeCoin.isChainValid();
}

