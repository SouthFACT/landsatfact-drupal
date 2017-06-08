
<?php

return array(
  'from' => 'info@southfact.com',
  'subject' => 'SouthFACT Area of Interest Change Analysis - {AOI_EVENT_DAY}, {AOI_EVENT_DATE}',
  'body' => <<<EOT

You are receiving this email because you subscribed to receive notifications for an area(s) of interest that you specified and this email is to inform you that a new change analysis has been generated.<br><br>

To view summary information of the change analysis and to view data products for your area of interest please click on the link next to the area below:<br><br>

{AOI_NAME}: <a href="{AOI_PARENT_URL}">{AOI_PARENT_URL}</a>.<br><br>

To manage your account and subscriptions, or to unsubscribe, please go here: <a href="http://www.southfact.com/aoi">http://www.southfact.com/aoi?source=email</a><br>

EOT

);
