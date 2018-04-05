<!DOCTYPE html>
<html>
<head>
    <title>Configuration Updated</title>
    <meta name="viewport" content="width=device-width, height=device-height, initial-scale=1.0"/>
<link rel="stylesheet" href="css/jquery.mobile-1.4.5.min.css">
<script src="js/jquery-1.11.3.min.js"></script>
<script src="js/jquery.mobile-1.4.5.min.js"></script>
<script>
setTimeout(function(){
    $.mobile.changePage('#page2',{transtion:'none'});   
},1000);
 </script>
</head>
<body>
    <div data-role="page2" id="second" data-add-back-btn="true" data-back-btn-text="Back">
        <div data-theme="a" data-role="header">
            <h3>Saved!</h3>
        </div>

        <div data-role="content">
            
	<?php  
		if(!empty($_POST['brightness']) && !empty($_POST['sw']) && !empty($_POST['thm']) && !empty($_POST['timeS']) && !empty($_POST['timeE']) ) {
			    $data = $_POST['brightness'] . "\n" . $_POST['sw'] . "\n" . $_POST['thm'] . "\n" . $_POST['timeS'] . "\n" . $_POST['timeE'];
			    $ret = file_put_contents('/home/leds/leds/conf/conf.txt', $data, LOCK_EX);
			    if($ret === false) {
			        die('There was an error writing this file');
    				}  
    			else {
       				 echo "Config Successfully Saved.";
    			}
		}
		else { 
  			 die('There was an error saving your setting. Please try again.');
		} 
	?>
        </div>
    </div>
</body>


</html>

