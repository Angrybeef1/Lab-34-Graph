What to submit: your GitHub repo URL.

Your starting graph is the one from this module's lesson on graphs:

image-1ba213a8-fe25-46f6-95c9-f3594a000d2d.png

Feed this module's demo code into a large language model.

Step 1
Through prompt engineering, transform the code by adding the necessary code to do a DFS and BFS in your code. Write a short driver program to exercise your code.

Complete Step 1 with a specific commit comment "Step 1 complete."

Sample Output
Graph's adjacency list:
0 --> (1, 12) (2, 8) (3, 21) 
1 --> (0, 12) 
2 --> (0, 8) (3, 6) (6, 2) (4, 4) (5, 5) 
3 --> (0, 21) (2, 6) 
4 --> (5, 9) (2, 4) 
5 --> (6, 6) (4, 9) (2, 5) 
6 --> (2, 2) (5, 6) 
DFS starting from vertex 0:
0 3 2 5 4 6 1
BFS starting from vertex 0:
0 1 2 3 6 4 5
 

 

Step 2
Change the graph by deleting at least two nodes and adding at least six nodes. Change the weights as well. 

Complete Step 2 with a specific commit comment "Step 2 complete."

Sample Output
Graph's adjacency list:
0 --> (1, 8) (2, 21)
1 --> (0, 8) (2, 6) (3, 5) (4, 4)
2 --> (0, 21) (1, 6) (7, 11) (8, 8)
3 --> (1, 5) (4, 9)
4 --> (1, 4) (3, 9)
5 --> (6, 10) (7, 15) (8, 5)
6 --> (5, 10) (7, 3) (8, 7)
7 --> (6, 3) (5, 15) (2, 11)
8 --> (5, 5) (6, 7) (2, 8)
DFS starting from vertex 0:
0 2 8 6 5 7 1 4 3
BFS starting from vertex 0:
0 1 2 3 4 7 8 6 5
 

Step 3
Through expert prompt engineering, wrap an application around this new graph. It should be some real-world example that is represented by your graph.

Complete Step 3 with a specific commit comment "Step 3 complete."

Here's an example (you can't use this, haha) in which a graph could represent a network of water distribution pipes.

Sample Output
Water Pipeline Network Topology:
================================
Junction 0 (Pump Station) connects to:
  → Junction 1 (Capacity: 800 GPM)
  → Junction 2 (Capacity: 2100 GPM)
Junction 1 (Distribution Hub) connects to:
  → Junction 0 (Capacity: 800 GPM)
  → Junction 2 (Capacity: 600 GPM)
  → Junction 3 (Capacity: 500 GPM)
  → Junction 4 (Capacity: 400 GPM)
Junction 2 (Reservoir) connects to:
  → Junction 0 (Capacity: 2100 GPM)
  → Junction 1 (Capacity: 600 GPM)
  → Junction 7 (Capacity: 1100 GPM)
  → Junction 8 (Capacity: 800 GPM)
Junction 3 (Treatment Plant) connects to:
  → Junction 1 (Capacity: 500 GPM)
  → Junction 4 (Capacity: 900 GPM)
Junction 4 (Storage Tank) connects to:
  → Junction 1 (Capacity: 400 GPM)
  → Junction 3 (Capacity: 900 GPM)
Junction 5 (Distribution Hub) connects to:
  → Junction 6 (Capacity: 1000 GPM)
  → Junction 7 (Capacity: 1500 GPM)
  → Junction 8 (Capacity: 500 GPM)
Junction 6 (Control Valve) connects to:
  → Junction 5 (Capacity: 1000 GPM)
  → Junction 7 (Capacity: 300 GPM)
  → Junction 8 (Capacity: 700 GPM)
Junction 7 (Storage Tank) connects to:
  → Junction 6 (Capacity: 300 GPM)
  → Junction 5 (Capacity: 1500 GPM)
  → Junction 2 (Capacity: 1100 GPM)
Junction 8 (Pump Station) connects to:
  → Junction 5 (Capacity: 500 GPM)
  → Junction 6 (Capacity: 700 GPM)
  → Junction 2 (Capacity: 800 GPM)

Network Trace (DFS) from Junction 0 (Pump Station):
Purpose: Tracing possible contamination paths through the network        
=======================================
Inspecting Junction 0 (Pump Station)
  → Potential spread to Junction 1 (Distribution Hub) - Capacity: 800 GPM
  → Potential spread to Junction 2 (Reservoir) - Capacity: 2100 GPM      
Inspecting Junction 2 (Reservoir)
  → Potential spread to Junction 7 (Storage Tank) - Capacity: 1100 GPM   
  → Potential spread to Junction 8 (Pump Station) - Capacity: 800 GPM    
Inspecting Junction 8 (Pump Station)
  → Potential spread to Junction 5 (Distribution Hub) - Capacity: 500 GPM
  → Potential spread to Junction 6 (Control Valve) - Capacity: 700 GPM   
Inspecting Junction 6 (Control Valve)
Inspecting Junction 5 (Distribution Hub)
Inspecting Junction 7 (Storage Tank)
Inspecting Junction 1 (Distribution Hub)
  → Potential spread to Junction 3 (Treatment Plant) - Capacity: 500 GPM 
  → Potential spread to Junction 4 (Storage Tank) - Capacity: 400 GPM    
Inspecting Junction 4 (Storage Tank)
Inspecting Junction 3 (Treatment Plant)

Layer-by-Layer Network Inspection (BFS) from Junction 0 (Pump Station):  
Purpose: Analyzing service areas by distance from source
=================================================
Checking Junction 0 (Pump Station)
  → Next service area: Junction 1 (Distribution Hub) - Capacity: 800 GPM 
  → Next service area: Junction 2 (Reservoir) - Capacity: 2100 GPM       
Checking Junction 1 (Distribution Hub)
  → Next service area: Junction 3 (Treatment Plant) - Capacity: 500 GPM  
  → Next service area: Junction 4 (Storage Tank) - Capacity: 400 GPM     
Checking Junction 2 (Reservoir)
  → Next service area: Junction 7 (Storage Tank) - Capacity: 1100 GPM    
  → Next service area: Junction 8 (Pump Station) - Capacity: 800 GPM     
Checking Junction 3 (Treatment Plant)
Checking Junction 4 (Storage Tank)
Checking Junction 7 (Storage Tank)
  → Next service area: Junction 6 (Control Valve) - Capacity: 300 GPM    
  → Next service area: Junction 5 (Distribution Hub) - Capacity: 1500 GPM
Checking Junction 8 (Pump Station)
Checking Junction 6 (Control Valve)
Checking Junction 5 (Distribution Hub)
 

Step 4
Through prompt engineering add code to provide the shortest path through your graph.

Complete Step 4 with a specific commit comment "Step 4 complete."

Sample Output
Shortest path from node 0:
0 -> 0 : 0
0 -> 1 : 8
0 -> 2 : 14
0 -> 3 : 13
0 -> 4 : 12
0 -> 5 : 27
0 -> 6 : 28
0 -> 7 : 25
0 -> 8 : 22
 

Step 5
Through prompt engineering, add code to provide the minimum spanning tree of your graph.

Complete Step 5 with a specific commit comment "Step 5 complete."

Sample Output
Minimum Spanning Tree edges:
Edge from 1 to 0 with capacity: 8 units
Edge from 4 to 1 with capacity: 4 units
Edge from 3 to 1 with capacity: 5 units
Edge from 2 to 1 with capacity: 6 units
Edge from 8 to 2 with capacity: 8 units
Edge from 5 to 8 with capacity: 5 units
Edge from 6 to 8 with capacity: 7 units
Edge from 7 to 6 with capacity: 3 units
 

Step 6
Place a menu in front of all this functionality.

Complete Step 6 with a specific commit comment "Step 6 complete."

Sample Output
Water Distribution Network Menu:
[1] Display water distribution network
[2] Check contaminant spread (BFS)
[3] Plan inspection route  (DFS)
[4] Calculate shortest paths
[5] Find Minimum Spanning Tree
[0] Exit
Enter your choice: 
