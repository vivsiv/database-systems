<?php
	include 'db_functions.php';
	if($_GET["create_review"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$name = sanitize_string($_GET["review_name"], $db_connection);
		$date = date('Y-m-d H:i:s');
		print $date . "<br/>";
		$mid = sanitize_string($_GET["movie_id"], $db_connection);
		$rating = sanitize_string($_GET["rating"], $db_connection);
		$comment = sanitize_string($_GET["comment"], $db_connection);

		$review_base_query = "insert into Review values ('%s', '%s', %d, %d, '%s')";
		$review_query = sprintf($review_base_query, $name, $date, $mid, $rating, $comment);
		print $review_query . "<br/>";
		run_query($review_query, $db_connection);

		close_connection($db_connection);
	}


?>