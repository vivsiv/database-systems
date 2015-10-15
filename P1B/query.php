<h1>Movie Database</h1>
<p>(Ver 1.0) by Vivek Sivakumar</p>
<hr/>


<p>Available Tables</p>
<ul>
	<li>Movie</li>
	<li>Actor</li>
	<li>Director</li>
	<li>Review</li>
</ul>
<hr/>

<p>Type an SQL Query into the box</p>
<p>
<form action="query.php" method="GET">
	<textarea name="query" rows="5" cols="50"></textarea>
	<br/><br/>
	<input type="submit" value="Search">
</form>
</p>
<hr/>

<?php
	if($_GET["query"]){
		$query = $_GET["query"];
		echo "Queried: " . $query;
		//echo "Result: ";
	}
?>