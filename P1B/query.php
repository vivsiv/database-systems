<h1>Movie Database</h1>
<p>(Ver 1.0) by Vivek Sivakumar</p>
<hr/>


<p>Available Tables</p>
<ul>
	<li>Movie</li>
	<li>Actor</li>
	<li>Director</li>
	<li>MovieGenre</li>
	<li>MovieActor</li>
	<li>MovieDirector</li>
	<li>Review</li>
</ul>
<hr/>

<p>Type an SQL Query into the box</p>

<?php
	function printForm($query=NULL){
		print "<p>";
		print "<form action='query.php' method='GET'>";
		print "<textarea name='query' rows='5' cols='50'>";
		if ($query) print $query;
		print "</textarea>";
		print "<br/><br/>";
		print "<input type='submit' value='Search'>";
		print "</form>";
		print "</p>";
		print "<hr/>";
	}

	if($_GET["query"]){
		$query = $_GET["query"];
		printForm($query);
		print "<b>Queried</b>: '" . $query . "'";
		print "<br/><br/>";
		$db_connection = mysql_connect("localhost", "cs143", "");
		if (!$db_connection){
			$error_msg = mysql_error($db_connection);
			print "Connection Failed: $error_msg <br/>";
			exit(1);
		}
		$db_selected = mysql_select_db("TEST", $db_connection);
		if (!$db_selected){
			print "Database doesn't exist! <br/>";
			exit(1);
		}
		$sanitized_query = $query;
		$result = mysql_query($sanitized_query, $db_connection);
		if (!$result){
			$error_msg = mysql_error($db_connection);
			print "<b>Query Error:</b> $error_msg <br/>";
			exit(1);
		}
		mysql_close($db_connection);

		print "<table border='3'>";
		$num_cols = mysql_num_fields($result);
		print "<tr>";
		for ($i = 0; $i < $num_cols; $i++){
			print "<th border='2'>".mysql_field_name($result, $i)."</th>";
		}
		print "</tr>";
		while ($row = mysql_fetch_row($result)){
			print "<tr>";
				foreach ($row as $val){
					print "<td border='1'>".$val."</td>";
				}
			print "</tr>";
		}
		print "</table>";
	}
	else {
		printForm();
	}
?>