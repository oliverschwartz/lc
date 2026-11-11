class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {

        unordered_map<string, vector<string>> in_to_rep; // ingredient can be a recipe
        unordered_map<string, unordered_set<string>> rep_to_in; 

        for (int i = 0; i < recipes.size(); ++i)
        {
            for (auto& in : ingredients[i])
            {
                in_to_rep[in].push_back(recipes[i]);
                rep_to_in[recipes[i]].insert(in);
            }
        }

        unordered_set<string> ret; 
        
        while (supplies.size())
        {
            vector<string> swp;
            for (auto& s : supplies)
            {
                for (auto& r : in_to_rep[s])
                {
                    rep_to_in[r].erase(s);
                    if (rep_to_in[r].empty())
                    {
                        ret.insert(r);
                        swp.push_back(r);
                    }
                }
            }
            std::swap(swp, supplies);
        }

        vector<string> v;
        for (auto& s : ret)
        {
            v.push_back(s);
        }
        return v;
    }
};
