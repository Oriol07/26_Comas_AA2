#pragma once


//Struct que conté els elements necessaris del ranking
struct ranking
{
	unsigned int score;
	std::string name;
};

//Agafem les dades del ranking i les posem al map
void readRanking(std::map<std::string, unsigned int>& r)
{
	ranking gRank;
	std::ifstream readRank;
	readRank.open("Ranking.txt");
	while (!readRank.eof())
	{
		readRank >> gRank.score;
		readRank >> gRank.name;

		r[gRank.name] = gRank.score;
	}
	readRank.close();
}
void writeRanking(const std::string name, const unsigned int score)
{
	std::ofstream writeRank;
	writeRank.open("Ranking.txt", std::ofstream::app);
	writeRank << std::endl << score << " " << name;
	
	writeRank.close();

}

//passem les dades de un std::map a un std::list
void swapRanking(std::map<std::string, unsigned int>& r, std::list<ranking>& rList)
{
	ranking gRank;
	rList.clear();
	int count = 0;
	for (std::map<std::string, unsigned int>::iterator it = r.begin(); it != r.end(); ++it)
	{
		gRank.name = it->first;
		gRank.score = it->second;
		rList.push_back(gRank);
	}
}

// Funció que ens ajuda a ordenar el ranking mitjançant el nostre struct.
bool compareBig(const ranking& first, const ranking& second)
{
	if (first.score > second.score)
	{
		return true;
	}
	else return false;

}