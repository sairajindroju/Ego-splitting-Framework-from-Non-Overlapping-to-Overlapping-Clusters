library(Dict)
library(tidyverse)
new.Read_data <- function(input_file) {
  data=read.csv(input_file)
  return(data)
}

new.Get_nodes <- function(dataframe) {
  dataframe = as.list(dataframe)
  data = sapply(dataframe, unique)
  nodes = union(data$id1,data$id2)
  return(nodes)
}

new.Get_neighbour_edges  <- function(dataframe, neighbours){
  temp_e0 = list()
  temp_e1 = list()
  e0 = dataframe$id1
  e1 = dataframe$id2
  for (index in 1:length(e0)){
    if(e0[index] %in% neighbours){
      if(e1[index] %in% neighbours){
        temp_e0 <- append(temp_e0,e0[index])
        temp_e1 <- append(temp_e1,e1[index])
      }
    }
  }
  id1 = unlist(temp_e0)
  id2 = unlist(temp_e1)
  neighbour_edges = data.frame(id1,id2)
  return(neighbour_edges)
}
new.Get_neighbours <- function(dataframe, node){
  neighbours = list()
  e0 = dataframe$id1
  e1 = dataframe$id2
  for (index in 1:length(e0)){
    if(e0[index]==node){
      neighbours <- append(neighbours,e1[index])
    }
    if(e1[index]==node){
      neighbours <- append(neighbours,e0[index])
    }
  }
  return(neighbours)
}

new.Get_conncected_componenets <- function(dataframe){
  connected_comps = list()
  e0 = dataframe$id1
  e1 = dataframe$id2
  temp = list()
  count = 1
  index_temp = list()
  while(length(e0)){
    for (index in 1:length(e0)){
      if (index == 1){
        index_temp <- append(index_temp,index)
        temp <- append(temp, list(e0[index],e1[index]))
      }
      else{
      if ( e0[index] %in% temp ){
        if (!(e1[index] %in% temp )){
          index_temp <- append(index_temp,index)
          temp <- append(temp, e1[index])
        }
      }
      if ( e1[index] %in% temp ){
        if (!(e0[index] %in% temp )){
          index_temp <- append(index_temp,index)
          temp <- append(temp, e0[index])
        }
      }
        if ( e1[index] %in% temp ){
          if (e0[index] %in% temp ){
            index_temp <- append(index_temp,index)
          }
        }
      }
    }
    index_temp = list(a=index_temp)
    index_temp=sapply(index_temp, unique)
    index_temp=sapply(c(index_temp),unique)
    dataframe = dataframe[-index_temp,]
    e0 = dataframe$id1
    e1 = dataframe$id2
    connected_comps<-c(connected_comps, list(temp))
    count = count+1
    index_temp=list()
    #print(sapply(temp, unique))
    temp = list()
  }
  return(connected_comps)
}
new.Get_persona_graph_edges <- function(dataframe,components){
  persona_graph_edges <- data.frame(matrix(ncol = 2, nrow = 0))
  colnames(persona_graph_edges) <- c('id1', 'id2')
  e0 = dataframe$id1
  e1 = dataframe$id2
  components_node = components$node_
  components_cc = components$cc_node
  components_index = components$index_
  for (index in 1:length(e0)){
    for (new_index in 1:length(components_node)){
      if (components_node[new_index]==e0[index]){
        if (components_cc[new_index]==e1[index]){
          temp1 = components_index[new_index]
        }
      }
      if (components_node[new_index]==e1[index]){
        if (components_cc[new_index]==e0[index]){
          temp2 = components_index[new_index]
        }
      }
    }
    persona_graph_edges=persona_graph_edges %>% add_row(id1 = temp1, id2 = temp2)
  }
  return(persona_graph_edges)
}
  
input_file = 'inputs/test_edges.csv'
data1 = new.Read_data(input_file)
colnames(data1) <- c('id1', 'id2')
nodes = new.Get_nodes(data1)
components_ <- data.frame(matrix(ncol = 3, nrow = 0))
colnames(components_) <- c('node_', 'cc_node', 'index_')
personalities_ <- data.frame(matrix(ncol = 2, nrow = 0))
colnames(personalities_) <- c('node_', 'index_')
index = 0
for (node in nodes){
  neighbours = new.Get_neighbours(data1, node)
  ego_net_minus_ego = new.Get_neighbour_edges(data1, neighbours)
  Connected_components = new.Get_conncected_componenets(ego_net_minus_ego)
  for (val in 1:length(Connected_components)){
    personalities_=personalities_ %>% add_row(node_ = node, index_ = index)
    for (comp in Connected_components[val]){
      for (val in comp){
        components_=components_ %>% add_row(node_ = node, cc_node=val,index_ = index)
      }
    }
    index = index+1
  }
}
print(components_)
persona_graph_edges = new.Get_persona_graph_edges(data1,components_)
print(persona_graph_edges)
