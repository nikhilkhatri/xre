

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
				'background-color': '#666',
				'label': 'data(id)'
			}
		},

		{
			selector: 'edge',
			style: {
				'width': 1,
				'line-color': '#f00',
				'mid-target-arrow-color': '#00f',
				'mid-target-arrow-shape': 'triangle',
				'label': function(ele){
					// console.log(ele);
					return ele._private.data.id.split("_")[1];
				}
			}
		}
	],

	layout: {
		name: 'grid',
		rows: 1
	}
}
