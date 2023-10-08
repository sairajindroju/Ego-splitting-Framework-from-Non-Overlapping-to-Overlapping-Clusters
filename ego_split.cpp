#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>


using namespace std;

//function to read CSV file data or edge data
vector<int> read_csv(string FileName,int node)
{
    ifstream file(FileName);
    vector<int> nodes1;
    vector<int> nodes2;  
    string line;
    string temp ="";
    int count=0;
    int row=0;
    while (getline(file, line)){
        line=line+",";
        if(row!=0){
            for (int i =0; i< line.length(); i++){
                if(line[i]!=','){
                    temp+=line[i];
                }
                else{
                    if(count == 0){
                        nodes1.push_back(stoi(temp));
                        count++;
                    }
                    else{
                        nodes2.push_back(stoi(temp));
                        count=0;
                    }
                    temp ="";
                }
                row++;
            }
        }
        else
        row++;
        temp ="";
    }
    if(node==0)
    return nodes1;
    else
    return nodes2;
}
//function to get unique values from single vector
vector<int> unique_vector_values(vector<int> nodes){
    sort(nodes.begin(), nodes.end());
    auto it = unique(nodes.begin(), nodes.end());
    vector<int> result;
    nodes.resize(distance(nodes.begin(), it));
    for (it = nodes.begin(); it!=nodes.end(); ++it)
    result.push_back(*it);
    return result;
}
//function to get unique valuse from two vectors which returns all nodes inour data set
vector<int> unique_values(vector<int> nodes1, vector<int> nodes2){
    vector<int> nodes_merged;
    nodes_merged = nodes1;
    for (const int& i : nodes2)
    nodes_merged.push_back(i);
    vector<int> unique_nodes;
    unique_nodes = unique_vector_values(nodes_merged);
    return unique_nodes;
}

//function to return neighbours of a given node from edges
vector<int> get_neighbours(vector<int> nodes1, vector<int> nodes2, int node){
    vector<int> neighours;
    int count =0;
    for (const int& i : nodes1){
        if(i==node)
        neighours.push_back(nodes2.at(count));
        count++;
    }
    count = 0;
    for (const int& i : nodes2){
        if(i==node)
        neighours.push_back(nodes1.at(count));
        count++;
    }
    return unique_vector_values(neighours);
}

//function to find vector intersections
vector<int> vector_intersection(vector<int> vector1,vector<int> vector2){
    vector<int> intersected;
    for (const int& node1 : vector1){
        for (const int& node2 : vector2){
            if(node1==node2)
            intersected.push_back(node1);
        }
    }
    return intersected;
}

//function to get all neighbouring edges from the given neighbours list
vector<int> get_neighbouring_edges(vector<int> nodes1, vector<int> nodes2, vector<int> neighbours){
    vector<int> node1_indexes;
    vector<int> node2_indexes;
    for (const int& neighbour : neighbours) {
        int index = 0;
        for (const int& node : nodes1) {
            if(neighbour == node)
            node1_indexes.push_back(index);
            index++;
        }
        index = 0;
        for (const int& node : nodes2) {
            if(neighbour == node)
            node2_indexes.push_back(index);
            index++;
        }
    }
    return vector_intersection(node1_indexes,node2_indexes);
}

bool contains(vector<int> vec, int elem)
{
    bool result = false;
    if( find(vec.begin(), vec.end(), elem) != vec.end() )
    result = true;
    return result;
}
//function to retun all connected componets for a given neighbouring edges of a node
map<int,vector<int> > get_componenets(vector<int> nodes1, vector<int> nodes2, vector<int> indexes){
    vector<int> node1_edges;
    vector<int> node2_edges;
    for (const int& index : indexes) {
        node1_edges.push_back(nodes1.at(index));
        node2_edges.push_back(nodes2.at(index));
    }
    set<set<int> > components;
    set<set<int> > temp_components;
    set<int> temp;
    int u,v;
    for(int i=0; i<node1_edges.size(); i++){
        u= node1_edges.at(i);
        v= node2_edges.at(i);

        temp.insert(u);
        temp.insert(v);
        temp_components = components;
        for(set<int> comp : components){
            auto it1 = comp.find(u);
            auto it2 = comp.find(v);
            if(it1 != comp.end() || it2 != comp.end()){
                temp_components.erase(comp);
                temp.insert(comp.begin(),comp.end());
            }
        }
        temp_components.insert(temp);
        components = temp_components;
        temp.clear();
    }
    map<int,vector<int> > final_components;
    vector<int> temp1;
    int count =0;
    for(set<int> s: components){
        for(int i: s)
        temp1.push_back(i);
        final_components[count]=temp1;
        count++;
        temp1.clear();
    }
    return final_components;
}
//Function to return all connectected components from the given edges list
map<int,int> get_partitions(vector<int> nodes1, vector<int> nodes2){
    vector<int> node1_edges;
    vector<int> node2_edges;
    node1_edges=nodes1;
    node2_edges=nodes2;
    set<set<int> > components;
    set<set<int> > temp_components;
    set<int> temp;
    int u,v;
    for(int i=0; i<node1_edges.size(); i++){
        u= node1_edges.at(i);
        v= node2_edges.at(i);

        temp.insert(u);
        temp.insert(v);
        temp_components = components;
        for(set<int> comp : components){
            auto it1 = comp.find(u);
            auto it2 = comp.find(v);
            if(it1 != comp.end() || it2 != comp.end()){
                temp_components.erase(comp);
                temp.insert(comp.begin(),comp.end());
            }
        }
        temp_components.insert(temp);
        components = temp_components;
        temp.clear();
    }
    map<int,int>  final_components;
    int count =0;
    for(set<int> s: components){
        for(int i: s)
        final_components[i]=count;
        count++;
    }
    return final_components;
}
//Function to return all neighbouring nodes of a node from the gien dataset
vector<int> get_neighbours_new(vector<int> nodes1, vector<int> nodes2, int node){
    vector<int> neighbours;
    for(int i=0; i< nodes1.size(); i++){
        if(nodes1.at(i)==node & nodes2.at(i)!=node)
        neighbours.push_back(nodes2.at(i));
        if(nodes2.at(i)==node & nodes1.at(i)!=node)
        neighbours.push_back(nodes1.at(i));
    }
    return neighbours;
}

int main()
{
    // initiate filename
    string file_name = "inputs/tester_edges.csv";

    // copy edges into node1, node2 vectors
    vector<int> nodes1;
    nodes1 = read_csv(file_name,0);
    vector<int> nodes2;
    nodes2 = read_csv(file_name,1);

    //intialize variables
    //components_ to save final communities of each node
    //personalities_ to save personalities/communities assigned to each node
    int index=0;
    map<int, map<int,int> > components_;
    map<int, vector<int> > personalities_;
    vector<int> temp_indexes_new;
    map<int,int> temp_node_indexs;

    //get all nodes from the data set
    vector<int> nodes;
    nodes = unique_values(nodes1,nodes2);
    

    for (const int& node : nodes) {
        cout<<"####################################################################\nFor node : "<<node<<"\n\nNeighbours are : ";
        //get supgraph edge indexs (ego nets without ego's)from neighbours of a node
        vector<int> neighbours;
        neighbours=get_neighbours_new(nodes1,nodes2,node);
        for(const int& neighbour : neighbours)
        cout<<neighbour<<" , ";
        cout<<"\n\nNeighbouring edges are :";
        vector<int> neighbour_edge_indexes;
        neighbour_edge_indexes = get_neighbouring_edges(nodes1,nodes2,neighbours);
        for(const int& neighbour_edge_index : neighbour_edge_indexes)
        cout<<"("<<nodes1.at(neighbour_edge_index)<<" , "<<nodes2.at(neighbour_edge_index)<<"), ";
        cout<<"\n\nComponents are\n";

        //get components of neighbours 
        map<int,vector<int> >  components;
        components = get_componenets(nodes1,nodes2,neighbour_edge_indexes);
        
        //Format components as per requirments
        int temp_neighbour_count=0;
        int temp_components_size=components.size();
        for(const int& neighbour : neighbours){
            for(int k=0; k<temp_components_size; k++){
                for (const int& component : components[k]){
                    if(component==neighbour)
                    temp_neighbour_count++;
                }
            }
            if(temp_neighbour_count==0){
                components[components.size()].push_back(neighbour);
            }
            temp_neighbour_count=0;
        } 
        
        for(const auto& [k,v] : components){
            cout<<k;
            cout<<"  { ";
            for (const int& component : components[k]) 
            cout<<component<<" , ";
            cout<< "}\n";
        }

        //map personalities using component data into temp_indexes_new vector
        cout<<"\n\nPersonalities are : ";
        for(int i=0; i< components.size();  i++){
            temp_indexes_new.push_back(index);
            for(const int& j : components[i]){
                temp_node_indexs[j]=index;
            }
            index++;
        }
        for(const int& personality : temp_indexes_new)
        cout<<personality<<" , ";
        cout<<"\n\n";
        //map personalities for each node to global personalities_ valiable for the given node
        personalities_[node]=temp_indexes_new;
        //map neighbouring components for each node
        components_[node]=temp_node_indexs;
        temp_indexes_new.clear();
        temp_node_indexs.clear();
    }
    //create a personality map using personalities_ generated for each node
    map<int, int> personality_map;
    for(const auto& [k,v] : personalities_){
        for(const int& i : personalities_[k])
        personality_map[i]=k;
    }
    cout<<"Final components are \n {";
    for(const auto& [k,v] : components_){
        cout<<k<<"\n";
        for(const auto& [k1,v1] : components_[k])
        cout<<"{"<<k1<<" : "<<components_[k][k1]<<"}\n";
    }
    cout<<"}\nPersonality mappings are : {";
    for(const auto& [k,v] : personality_map){
        cout<<k<<" : "<<personality_map[k]<<" , ";
    }
    //create persona graph edges using components_
    cout<<"}\n\nPersona Graph edges are : { ";
    vector<int> persona_graph_edges_node1;
    vector<int> persona_graph_edges_node2;
    for(int i=0; i<nodes1.size();i++){
        persona_graph_edges_node1.push_back(components_[nodes1.at(i)][nodes2.at(i)]);
        persona_graph_edges_node2.push_back(components_[nodes2.at(i)][nodes1.at(i)]);
    }
    for(int i=0; i< persona_graph_edges_node1.size();i++)
    cout<<" ( "<<persona_graph_edges_node1.at(i)<<" , "<<persona_graph_edges_node2.at(i)<<" ), ";
    cout<<"}\n\nPartitions are : { ";

    //create partetions for persona graph using data from get_partetions function
    map<int, int > partitions;
    partitions = get_partitions(persona_graph_edges_node1,persona_graph_edges_node2);
    for(const auto& [k,v] : partitions)
        cout<<k<<" : "<<partitions[k]<<" , ";
    cout<<"}\n\nOverlapping Partitions for the orginal graph : \n{ ";

    //create overlapping partitions using personality map and persona graph partion data 
    map<int, vector<int> > overlapping_partitions;
    vector<int> temp;
    for (const int& node : nodes)
    overlapping_partitions[node]=temp;
    for(const auto& [k,v] : partitions)
    overlapping_partitions[personality_map[k]].push_back(partitions[k]);
    for(const auto& [k,v] : overlapping_partitions){
        cout<<k<<" : [";
        for(const int& i: overlapping_partitions[k] )
        cout<<i<<" , ";
        cout<<" ],";
    }
    cout<<"}\n\n";

}
