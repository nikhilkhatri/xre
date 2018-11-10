
parse_signal = function(sig){
	switch (sig.sigtype){
		case "SIGALOC":
			if(sig.source_region == "heap"){
				add_node(String(sig.source_addr), true); // known to be alloced on heap
				add_node(String(sig.dest),  true); // known to be alloced on heap
				
				var eid = String(sig.source_addr) + "_" + String(sig.source_index);
				
				add_edge(eid, String(sig.source_addr), String(sig.dest));
			}
			else {
				add_node(String(sig.source_addr), false); // assume anything not on heap is not alloced
				add_node(String(sig.dest), true); // known to be alloced on heap
				add_edge(String(sig.source_addr) + "_0", String(sig.source_addr), String(sig.dest));
			}
			break;
		case "SIGCOPY":
			if(sig.source_region == "heap"){
				add_node(String(sig.source_addr), true); // assume heap address already alloced
				add_node(String(sig.dest), true); // known to be alloced
				
				var eid = String(sig.source_addr) + "_" + String(sig.source_index);
				
				add_edge(eid, String(sig.source_addr), String(sig.dest));
			}
			else {
				add_node(String(sig.source_addr), false); // assume anything not on heap is not alloced
				add_node(String(sig.dest), true); // known to be allocated
				add_edge(String(sig.source_addr) + "_0", String(sig.source_addr), String(sig.dest));
			}
			break;
		case "SIGFREE":
			add_node(String(sig.addr), false);
			break;
		default:
			break;
	}
	// console.log(graph);
}