

// each node has additional attrib :
	// alloced : [true, false]


find_entity = function(id){
	var l = graph.elements.length;

	for(var i = 0; i<l; i ++){
		if (graph.elements[i].data.id == id){
			return i;
		}
	}
	return -1;
}

add_node = function(id, alloced){
	var l = graph.elements.length;

	for(var i = 0; i<l; i ++){
		if (graph.elements[i].data.id === id){
			graph.elements[i].data.alloced = alloced;
			return ;
		}
	}
	graph.elements.push(
		{
			"data": {"id": id, "alloced": alloced}
		}
	);
	console.log("pushed node");
	console.log(graph.elements);
}

add_edge = function(id, src, dest){
	var l = graph.elements.length;

	for(var i = 0; i<l; i ++){
		if (graph.elements[i].data.id == id){
			graph.elements[i].data = {"id": id, "source": src, "target": dest};
			return ;
		}
	}

	graph.elements.push(
		{
			"data": {"id": id, "source": src, "target": dest}
		}
	);
	console.log("pushed edge");
	console.log(graph.elements);
}

remove_edge = function(index){
	graph.elements.splice(index, 1);
}

graph = {

	container: document.getElementById('dagrediv'), // container to render in

	elements: [ // list of graph elements to start with
	],

	style: [ // the stylesheet for the graph
		{
			selector: 'node',
			style: {
				'background-color': function(ele){
					if(ele._private.data.id == "0"){
						return "#F00";
					}
					else if(ele._private.data.alloced == "H"){
						return "#000";
					}
					else if(ele._private.data.alloced == "S"){
						return "#ffb380";
					}
					else {
						return "#CCC";
					}
				},
				'label': function(ele) {
					return parseInt(ele._private.data.id).toString(16);
				}
			}
		},

		{
			selector: 'edge',
			style: {
				'width': 2,
				'line-color': '#faa',
				'mid-target-arrow-color': '#a77',
				'mid-target-arrow-shape': 'triangle',
				'arrow-scale': 2,
				'label': function(ele){
					// console.log(ele);
					return ele._private.data.id.split("_")[1];
				}
			}
		}
	],

	layout: {
		name: 'breadthfirst'
	}
}
