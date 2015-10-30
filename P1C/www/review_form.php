<?php
	include 'header.php';
	print "<body>";
?>
<h2>Add a Review for <?php print $_GET['movie_title'] ?></h2>
<form id="create_review" action="create_review.php" method="GET">
	<input name="create_review" type="hidden" value="true"/>
	<input type="text" name="movie_id" hidden="true" value="<?php print $_GET['movie_id'] ?>"/>
	<h4>Name</h4>
	<input type="text" name="review_name"/>
	<h4>Rating (1-5)</h4>
	<input type="text" name="rating"/>
	<h4>Comment</h4>
	<textarea type="text" name="comment"></textarea>
	<br/><br/>
	<input type='submit' value='Create Review'/>
</form>
<?php print "<body>"; ?>