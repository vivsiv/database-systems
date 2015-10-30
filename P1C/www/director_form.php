<?php include 'header.php' ?>
<body>
	<h2>Create Director</h2>
	<form id="create_director_form" action='create_person.php' method='GET'>
		<input name="create_person" type="hidden" value="true"/>
		<input name="person_type" type="hidden" value="director"/>
		<h4>First Name</h4>
		<input type="text" name="first"/>
		<h4>Last Name</h4>
		<input type="text" name="last"/>
		<h4>DOB</h4>
		<input type="text" name="dob"/>
		<h4>DOD</h4>
		<input type="text" name="dod"/>
		<br/><br/>
		<input type='submit' value='Create Director'/>
	</form>
	<hr/>
</body>