<!DOCTYPE html>
<html>
<head>
    <title>Configuration Updated</title>
    <link rel="stylesheet" href="css/lcd.css">
<script>
 </script>
</head>
<body>

    <h3>Status:</h3>
    

    <?php  
    function clean($string) {
       $sanitized = preg_replace('/([\|`~])+/', '', $string); // Removes special chars.

       return $sanitized; // Replaces multiple hyphens with single one.
    }

        $serialPort = `python -m serial.tools.list_ports | head -1`;
        $serialPort = trim($serialPort);
        $left = clean($_POST['left1']) . "|" . clean($_POST['left2']) . "|" . clean($_POST['left3']) . "|" . clean($_POST['left4']);
        $center = clean($_POST['center1']) . "|" . clean($_POST['center2']);
        $right = clean($_POST['right1']) . "|" . clean($_POST['right2']) . "|" . clean($_POST['right3']) . "|" . clean($_POST['right4']);
            $data = (string)$serialPort . "\n" . (string)$left . "`" . (string)$center . "`" . (string)$right . "~";
            $ret = file_put_contents('/home/leds/leds/conf/conf-lcd.txt', (string)$data, LOCK_EX);
            if($ret === false) {
                die('There was an error writing this file; Please try again.');
                }  
            else {
                 echo "Config Successfully Saved.";
            } 
    ?>

</body>


</html>

