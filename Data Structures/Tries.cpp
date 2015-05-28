/*
 * Author: Adarsh Pugalia
 * Algorithm: Implementation of tries.
 *				Insertion: O(N)
 * 				Search Word: O(N)
 *				Search Prefix: O(N)
 * 				Delete: O(N)
 *				N: the length of the string/prefix
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <set>
#include <queue>
#include <algorithm>
#include <stack>
#include <cmath>
#include <cassert>
 
#define ll long long int
#define vi vector <int>
#define vl vector <ll>
#define vpii vector <pair<int, int> >
#define vpll vector <pair<ll, ll> >
#define pll pair<ll, ll>
 
#define f first
#define s second
 
#define sd(n) scanf("%d", &n)
#define sl(n) scanf("%lld", &n)
 
#define pb push_back
#define pob pop_back
 
#define max_size 505
#define max_capacity INT_MAX
#define max_string_size 1000
#define max_node_size 340
#define max_power 26
#define max_sieve_size 105
 
#define MOD 1000000007
 
using namespace std;

class TrieNode
{
	public:
		ll words;
		ll prefixes;
		TrieNode* child[26];

		TrieNode()
		{
			words = 0;
			prefixes = 0;
			for(ll i=0; i<26; i++)
				child[i] = NULL;
		}
};

class Trie
{
	public:
		TrieNode *root;

		void init()
		{
			root = new TrieNode();
		}

		void insert(string word)
		{
			TrieNode *temp = root;
			ll position = 0;

			while(position<word.length())
			{
				temp->prefixes++;
				if(temp->child[word[position]-'a']==NULL)
					temp->child[word[position]-'a'] = new TrieNode();

				temp = temp->child[word[position]-'a'];
				position++;
			}

			temp->words++;
		}


		ll count_words(string word)
		{
			TrieNode *temp = root;
			ll position = 0;

			while(position<word.length())
			{
				if(temp->child[word[position]-'a']==NULL)
					return 0;

				temp = temp->child[word[position]-'a'];
				position++;
			}

			return temp->words;
		}


		ll count_prefixes(string prefix)
		{
			TrieNode *temp = root;
			ll position = 0;

			while(position<prefix.length())
			{
				if(temp->child[prefix[position]-'a']==NULL)
					return 0;

				temp = temp->child[prefix[position]-'a'];
				position++;
			}

			return temp->prefixes;
		}


		bool remove(string word)
		{
			TrieNode* temp = root;
			ll position = 0;

			while(position<word.length())
			{
				if(temp->child[word[position]-'a']==NULL)
				{
					TrieNode *temp2 = root;
					ll temp_position = 0;
					while(position!=temp_position)
					{
						temp2->prefixes++;
						temp2 = temp2->child[word[temp_position]-'a'];
						temp_position++;
					}
					return false;
				}

				temp->prefixes--;
				temp = temp->child[word[position]-'a'];
				position++;
			}

			temp->words--;
			return true;
		}
}trie;

int main()
{

	return 0;
}