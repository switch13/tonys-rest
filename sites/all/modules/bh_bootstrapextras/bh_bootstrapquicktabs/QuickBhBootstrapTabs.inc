<?php

/**
 * @file
 * Extends Quicktabs module's core functions.
 *
 */


/**
 * Renders the content using the Bootstrap Tabs widget.
 */
class QuickBhBootstrapTabs extends QuickRenderer {
  /**
   * Build admin form.
   */
  public static function optionsForm($qt) {
    $form = array();
    $form['tabtype'] = array(
      '#default_value' => (isset($qt->renderer) && $qt->renderer == 'bh_bootstrapquicktabs_tabs' && isset($qt->options['tabtype']) && $qt->options['tabtype']) ? $qt->options['tabtype'] : 'basic',
      '#description' => t('Choose the style of tab to use from %bootstrap', array('%bootstrap' => l(t('Bootstrap'), 'http://twitter.github.com/bootstrap/components.html#navs'))),
      '#options' => array(
        'basic' => t('Tabs on the top'),
        'left' => t('Tabs on the left'),
        'right' => t('Tabs on the right'),
        'below' => t('Tabs on the bottom'),
      ),
      '#title' => t('Type of tabs'),
      '#type' => 'radios',
    );
    return $form;
  } // optionsForm()


  /**
   * Build render array.
   */
  public function render() {
    $quickset = $this->quickset;
    $settings = $this->quickset->getSettings();
    $options = $settings['options'];
    $active_tab = $quickset->getActiveTab();
    $tabs = $this->build_tablinks($active_tab);
    $qt_name = $quickset->getName();
    $render_array = array(
      'content' => array(
        '#theme' => 'bh_bootstrapquicktabs_tabs',
        '#options' => array(
          'attributes' => array(
            'id' => 'quicktabs-' . $qt_name,
            'class' => 'tabbable' . ($options['tabtype'] != 'basic' ? ' tabs-' . $options['tabtype'] : ''),
          ),
        ),
        'tabs' => array(
          '#theme' => 'bh_bootstrapquicktabs_tabs_tabset',
          '#options' => array(
            'active' => $active_tab,
            'type' => $options['tabtype'],
          ),
          'tablinks' => $tabs,
        ),
        'panes' => array(),
      ),
    );

    foreach ($quickset->getContents() as $key => $tab) {
      if (!empty($tab)) {
        $attribs = array(
          'id' => 'quicktabs-' . $qt_name . ($key + 1),
        );
        $attribs['class'][] = 'tab-pane';
        if ($key == $active_tab) {
          $attribs['class'][] = 'active';
        }

        $render_array['content']['panes'][] = array(
          '#prefix' => '<div ' . drupal_attributes($attribs) . '>',
          '#suffix' => '</div>',
          'content' => $tab->render(),
        );
      }
    }

    return $render_array;
  } // render()


  /**
   * Build the actual tab links, with appropriate href, title and attributes.
   *
   * @param $active_tab The index of the active tab.
   */
  protected function build_tablinks($active_tab) {
    $tabs = array();
    $qt_name = $this->quickset->getName();
    foreach ($this->quickset->getContents() as $i => $tab) {
      if (!empty($tab)) {
        $attributes = array(
          'href' => '#quicktabs-' . $qt_name . ($i + 1),
          'data-toggle' => 'tab',
        );
        $markup = '<a ' . drupal_attributes($attributes) . '>' . check_plain($this->quickset->translateString($tab->getTitle(), 'tab', $i)) . '</a>';
        $tablink = array(
          '#markup' => $markup,
        );
        $tabs[$i] = $tablink;
      }
    }
    return $tabs;
  } // build_tablinks()
} // QuickBhBootstrapTabs
